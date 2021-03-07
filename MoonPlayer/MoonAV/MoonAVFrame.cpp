#include "MoonAV.h"

extern "C"{
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
}

#include "MoonAVFramePrivate.h"

namespace Moon {
    MoonAVFrame::MoonAVFrame() {
        p = new MoonAVFramePrivate();
        p->frame = av_frame_alloc();
    }

    MoonAVFrame::~MoonAVFrame() {
        av_frame_unref(p->frame);
        av_frame_free(&p->frame);
        if (p != nullptr) {
            delete p;
            p = nullptr;
        }

        for(int i=0;i<dataManager.size();i++){
            free(dataManager[i]);
        }
        dataManager.clear();
    }

    MoonAVFrame::MoonAVFrame(const MoonAVFrame & frame)
    {
        p = new MoonAVFramePrivate();
        p->frame = av_frame_alloc();
        *this = frame;
    }
    MoonAVFrame & MoonAVFrame::operator = (const MoonAVFrame & frame)
    {
        // Copy data
        // YUV 420 Data
        int width                           = frame.p->frame->width;
        int height                          = frame.p->frame->height;

        // Copy width ,height
        p->frame->width                  = frame.p->frame->width;
        p->frame->height                 = frame.p->frame->height;

        p->frame->channels               = frame.p->frame->channels;
        p->frame->channel_layout         = frame.p->frame->channel_layout;
        p->frame->nb_samples             = frame.p->frame->nb_samples;
        p->frame->format                 = frame.p->frame->format;
        p->frame->key_frame              = frame.p->frame->key_frame;
        p->frame->pict_type              = frame.p->frame->pict_type;
        p->frame->sample_aspect_ratio    = frame.p->frame->sample_aspect_ratio;
        p->frame->pts                    = frame.p->frame->pts;
        p->frame->pkt_dts                = frame.p->frame->pkt_dts;
        p->frame->coded_picture_number   = frame.p->frame->coded_picture_number;
        p->frame->display_picture_number = frame.p->frame->display_picture_number;
        p->frame->quality                = frame.p->frame->quality;

        // Copy linesize
        for(int i=0;i<AV_NUM_DATA_POINTERS;i++){
            p->frame->linesize[i] = frame.p->frame->linesize[i];
        }

        if(frame.getPixFormat() < 200 && frame.getPixFormat() >= 100){
            // 图像
            {
                int linesizeIndex = 0;
                int h = height;
                if(frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV420P || frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ420P){
                    h = height;
                }
                if(frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV444P || frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.p->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.p->frame->data[linesizeIndex], dataLen);

                p->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
            {
                int linesizeIndex = 1;
                int h = height;
                if(frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV420P || frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ420P){
                    h = height / 2;
                }
                if(frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV444P || frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.p->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.p->frame->data[linesizeIndex], dataLen);

                p->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
            {
                int linesizeIndex = 2;
                int h = height;
                if(frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV420P || frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ420P){
                    h = height / 2;
                }
                if(frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV444P || frame.getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.p->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.p->frame->data[linesizeIndex], dataLen);

                p->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
        }

        {
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
                int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)p->frame->format);
                int channelSize = p->frame->nb_samples * sizePerSample;

                for(int channelIndex=0; channelIndex<p->frame->channels; channelIndex++){
                    unsigned char * data = (unsigned char *)malloc(channelSize);
                    memcpy(data, frame.p->frame->data[channelIndex], channelSize);
                    p->frame->data[channelIndex] = data;
                    dataManager.push_back(data);
                }
            }
        }

        return *this;
    }

    int MoonAVFrame::getYData(unsigned char * yData)
    {
        int width = getWidth();
        int height = getHeight();

        int h = height;
        int w = width;

        if(getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV420P || getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ420P){
            h = height;
            w = width;
        }
        if(getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV444P || getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(yData + offset, p->frame->data[0] + i * p->frame->linesize[0], w);
            offset += w;
        }

        return 0;
    }

    int MoonAVFrame::getUVData(unsigned char * uvData)
    {
        int width = getWidth();
        int height = getHeight();

        int h = height;
        int w = width;

        if(getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVNV12 || getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVNV21){
            h = height / 2;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(uvData + offset, p->frame->data[1] + i * p->frame->linesize[1], w);
            offset += w;
        }

        return 0;
    }

    int MoonAVFrame::getUData(unsigned char * uData)
    {
        int width = getWidth();
        int height = getHeight();

        int h = height;
        int w = width;

        if(getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV420P || getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ420P){
            h = height / 2;
            w = width / 2;
        }
        if(getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV444P || getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(uData + offset, p->frame->data[1] + i * p->frame->linesize[1], w);
            offset += w;
        }

        return 0;
    }

    int MoonAVFrame::getVData(unsigned char * vData)
    {
        int width = getWidth();
        int height = getHeight();

        int h = height;
        int w = width;

        if(getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV420P || getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ420P){
            h = height / 2;
            w = width / 2;
        }
        if(getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV444P || getPixFormat() == MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(vData + offset, p->frame->data[2] + i * p->frame->linesize[2], w);
            offset += w;
        }
        return 0;
    }

    int MoonAVFrame::setPTS(int64_t pts)
    {
        p->frame->pts = pts;
        return 0;
    }

    int MoonAVFrame::getLineSize(int channel) {
        return p->frame->linesize[channel];
    }

    int MoonAVFrame::getWidth() {
        return p->frame->width;
    }

    int MoonAVFrame::getHeight() {
        return p->frame->height;
    }

    int64_t MoonAVFrame::getPTS()
    {
        return p->frame->pts;
    }

    int MoonAVFrame::getInfo() {
        printf("===============================================================\n");

        for(int i=0;i<AV_NUM_DATA_POINTERS;i++) {
            printf("Linesize [%d]: %d\n", i, p->frame->linesize[i]);
        }
        
        printf("Width: %d\n", p->frame->width);
        printf("Height: %d\n", p->frame->height);
        printf("Channels: %d\n", p->frame->channels);
        // printf("channel_layout: %lld\n", p->frame->channel_layout);
        printf("nb_samples: %d\n", p->frame->nb_samples);
        printf("format: %d\n", p->frame->format);

        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)p->frame->format);
        printf("Size Per Sample: %d\n", sizePerSample);

        {
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_RGB){
                printf("AVColorSpace: AVCOL_SPC_RGB\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_BT709){
                printf("AVColorSpace: AVCOL_SPC_BT709\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_UNSPECIFIED){
                printf("AVColorSpace: AVCOL_SPC_UNSPECIFIED\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_RESERVED){
                printf("AVColorSpace: AVCOL_SPC_RESERVED\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_FCC){
                printf("AVColorSpace: AVCOL_SPC_FCC\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_BT470BG){
                printf("AVColorSpace: AVCOL_SPC_BT470BG\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_SMPTE170M){
                printf("AVColorSpace: AVCOL_SPC_SMPTE170M\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_SMPTE240M){
                printf("AVColorSpace: AVCOL_SPC_SMPTE240M\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_YCGCO){
                printf("AVColorSpace: AVCOL_SPC_YCGCO\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_YCOCG){
                printf("AVColorSpace: AVCOL_SPC_YCOCG\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_BT2020_NCL){
                printf("AVColorSpace: AVCOL_SPC_BT2020_NCL\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_BT2020_CL){
                printf("AVColorSpace: AVCOL_SPC_BT2020_CL\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_SMPTE2085){
                printf("AVColorSpace: AVCOL_SPC_SMPTE2085\n");
            }
            /*
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_CHROMA_DERIVED_NCL){
                printf("AVColorSpace: AVCOL_SPC_CHROMA_DERIVED_NCL\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_CHROMA_DERIVED_CL){
                printf("AVColorSpace: AVCOL_SPC_CHROMA_DERIVED_CL\n");
            }
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_ICTCP){
                printf("AVColorSpace: AVCOL_SPC_ICTCP\n");
            }
            */
            if(p->frame->colorspace == AVColorSpace::AVCOL_SPC_NB){
                printf("AVColorSpace: AVCOL_SPC_NB\n");
            }
        }

        {
            if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUV420P){
                printf("Format: AV_PIX_FMT_YUV420P\n");
            }
            if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P){
                printf("Format: AV_PIX_FMT_YUVJ420P\n");
            }
            if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ422P){
                printf("Format: AV_PIX_FMT_YUVJ422P\n");
            }
            if(p->frame->format == AVPixelFormat::AV_PIX_FMT_RGB24){
                printf("Format: AV_PIX_FMT_RGB24\n");
            }
            if(p->frame->format == AVPixelFormat::AV_PIX_FMT_BGR24){
                printf("Format: AV_PIX_FMT_BGR24\n");
            }
            if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ444P){
                printf("Format: AV_PIX_FMT_YUVJ444P\n");
            }
            if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUV444P){
                printf("Format: AV_PIX_FMT_YUV444P\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_NONE){
                printf("Format: AV_SAMPLE_FMT_NONE\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8){
                printf("Format: AV_SAMPLE_FMT_U8\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16){
                printf("Format: AV_SAMPLE_FMT_S16\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32){
                printf("Format: AV_SAMPLE_FMT_S32\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLT){
                printf("Format: AV_SAMPLE_FMT_FLT\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_DBL){
                printf("Format: AV_SAMPLE_FMT_DBL\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8P){
                printf("Format: AV_SAMPLE_FMT_U8P\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16P){
                printf("Format: AV_SAMPLE_FMT_S16P\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32P){
                printf("Format: AV_SAMPLE_FMT_S32P\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
                printf("Format: AV_SAMPLE_FMT_FLTP\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_DBLP){
                printf("Format: AV_SAMPLE_FMT_DBLP\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S64){
                printf("Format: AV_SAMPLE_FMT_S64\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S64P){
                printf("Format: AV_SAMPLE_FMT_S64P\n");
            }
            if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_NB){
                printf("Format: AV_SAMPLE_FMT_NB\n");
            }
        }

        {
        }

        // Print Channel Layout
        {
            if(p->frame->channel_layout == AV_CH_LAYOUT_MONO){
                printf("Channel Layout: AV_CH_LAYOUT_MONO\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_STEREO){
                printf("Channel Layout: AV_CH_LAYOUT_STEREO\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_2POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_2POINT1\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_SURROUND){
                printf("Channel Layout: AV_CH_LAYOUT_SURROUND\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_2_1){
                printf("Channel Layout: AV_CH_LAYOUT_2_1\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_4POINT0){
                printf("Channel Layout: AV_CH_LAYOUT_4POINT0\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_3POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_3POINT1\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_5POINT0_BACK){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT0_BACK\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_5POINT0){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT0\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_5POINT1_BACK){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT1_BACK\n");
            }
            if(p->frame->channel_layout == AV_CH_LAYOUT_5POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT1\n");
            }
        }
        
        return 0;
    }

    MoonAVAudioDateType MoonAVFrame::getAudioDateType()
    {
        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8){
            return MoonAVAudioDateType::UNSIGNEDINT;
        }
        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8P){
            return MoonAVAudioDateType::UNSIGNEDINT;
        }



        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16){
            return MoonAVAudioDateType::SIGNEDINT;
        }
        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16P){
            return MoonAVAudioDateType::SIGNEDINT;
        }

        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32){
            return MoonAVAudioDateType::UNSIGNEDINT;
        }
        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32P){
            return MoonAVAudioDateType::UNSIGNEDINT;
        }



        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLT){
            return MoonAVAudioDateType::FLOAT;
        }
        if(p->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
            return MoonAVAudioDateType::FLOAT;
        }

        return MoonAVAudioDateType::UNSIGNEDINT;
    }

    MoonAVPixelFormat MoonAVFrame::getPixFormat() const {
        if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUV420P){
            return MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV420P;
        }
        if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P){
            return MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ420P;
        }
        if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUV444P){
            return MoonAVPixelFormat::Moon_AV_PIX_FMT_YUV444P;
        }
        if(p->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ444P){
            return MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVJ444P;
        }
        if(p->frame->format == AVPixelFormat::AV_PIX_FMT_NV12){
            return MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVNV12;
        }
        if(p->frame->format == AVPixelFormat::AV_PIX_FMT_NV21){
            return MoonAVPixelFormat::Moon_AV_PIX_FMT_YUVNV21;
        }

        return MoonAVPixelFormat::Moon_AV_PIX_FMT_UNKNOW;
    }

    int MoonAVFrame::getAudioPackedData(unsigned char * data)
    {
        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)p->frame->format);
        int bufferSize = sizePerSample * p->frame->nb_samples * p->frame->channels;
        if(data == nullptr){
            return bufferSize;
        }

        // 判断是 Packed 还是 Plane
        int isPanar = av_sample_fmt_is_planar((AVSampleFormat)p->frame->format);
        if(isPanar){
            // MoonLog("Panar\n");
            SwrContext * swrCtx = swr_alloc_set_opts(
                        NULL,
                        p->frame->channel_layout,
                        av_get_packed_sample_fmt((AVSampleFormat)p->frame->format),
                        p->frame->sample_rate,

                        p->frame->channel_layout,
                        (AVSampleFormat)p->frame->format,
                        p->frame->sample_rate,

                        0,
                        NULL
                        );


            swr_init(swrCtx);

            int ret = swr_convert(swrCtx, &data, p->frame->nb_samples, (const uint8_t **)p->frame->data, p->frame->nb_samples);

            swr_free(&swrCtx);
        }
        else{
            // MoonLog("Packed\n");
            memcpy(data, p->frame->data[0], bufferSize);
        }

        return 0;
    }

    int MoonAVFrame::setVideoData420P(unsigned char * _y, unsigned char * _u, unsigned char * _v, int _width, int _height)
    {
        unsigned char * y = (unsigned char *)malloc(_width * _height);
        memcpy(y, _y, _width * _height);

        unsigned char * u = (unsigned char *)malloc(_width * _height / 4);
        memcpy(u, _u, _width * _height / 4);

        unsigned char * v = (unsigned char *)malloc(_width * _height / 4);
        memcpy(v, _v, _width * _height / 4);

        dataManager.push_back(y);
        dataManager.push_back(u);
        dataManager.push_back(v);

        p->frame->format = AV_PIX_FMT_YUV420P;
        p->frame->width = _width;
        p->frame->height = _height;

        p->frame->linesize[0] = _width;
        p->frame->linesize[1] = _width / 2;
        p->frame->linesize[2] = _width / 2;

        p->frame->data[0] = y;
        p->frame->data[1] = u;
        p->frame->data[2] = v;

        /*
        int ret = av_image_alloc(p->frame->data, p->frame->linesize, _width, _height, AV_PIX_FMT_YUV420P, 16);

        MoonLog("=====================================\n");
        MoonLog("linesize[0]:%d\n", p->frame->linesize[0]);
        MoonLog("linesize[1]:%d\n", p->frame->linesize[1]);
        MoonLog("linesize[2]:%d\n", p->frame->linesize[2]);

        memcpy(p->frame->data[0], _y, _width * _height);
        memcpy(p->frame->data[1], _u, _width * _height / 4);
        memcpy(p->frame->data[2], _v, _width * _height / 4);
        */

        return 0;
    }

    int MoonAVFrame::getAudioData(unsigned char * data)
    {
        memcpy(data, p->frame->data[0], 8192 / 2);
        memcpy(data + 8192 / 2, p->frame->data[1], 8192 / 2);
        return 0;
    }

    int MoonAVFrame::getChannels()
    {
        return p->frame->channels;
    }

    int MoonAVFrame::getSampleRate()
    {
        return p->frame->sample_rate;
    }

    int MoonAVFrame::getNBSamples()
    {

        return p->frame->nb_samples;
    }

    int MoonAVFrame::getPerSampleSize()
    {
        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)p->frame->format);
        return sizePerSample;
    }

    int MoonAVFrame::initAACFrame(int channels)
    {
        if(channels >= AV_NUM_DATA_POINTERS){
            channels = AV_NUM_DATA_POINTERS;
        }

        p->frame->format = AVSampleFormat::AV_SAMPLE_FMT_FLTP;
        p->frame->channels = channels;
        p->frame->nb_samples = 1024;

        for(int channelIndex=0; channelIndex<channels; channelIndex++){
            int len = getPerSampleSize() * getNBSamples();

            unsigned char * d = (unsigned char *)malloc(len);
            memset(d, 0, len);

            p->frame->data[channelIndex] = d;
            dataManager.push_back(d);
        }
        return 0;
    }

    float MoonAVFrame::getAudioFloatData(int channel, int index)
    {
        if(channel >= getChannels()){
            return 0;
        }

        if(index >= getNBSamples()){
            return 0;
        }

        float * d = (float *)p->frame->data[channel];
        return d[index];
    }

    int MoonAVFrame::setAudioFloatData(int channel, int index, float d)
    {
        if(channel >= getChannels()){
            return 0;
        }

        if(index >= getNBSamples()){
            return 0;
        }

        float * dArr = (float *)p->frame->data[channel];
        dArr[index] = d;

        return 0;
    }

    //int MoonAVFrame::setAudioData(unsigned char * _data, int _dataLen, int nbSamples, int channel, MoonAVFormat _format)
    //{
    //    if(_format == MoonAVFormat::Moon_AV_SAMPLE_FMT_FLTP){
    //        // float, planar
    //        unsigned char * data = (unsigned char *)malloc(_dataLen);
    //        dataManager.push_back(data);

    //        memcpy(data, _data, _dataLen);

    //        p->frame->format = AV_SAMPLE_FMT_FLTP;
    //        p->frame->channels = channel;
    //        p->frame->nb_samples = nbSamples;
    //        int ret = avcodec_fill_audio_frame(p->frame, channel, AV_SAMPLE_FMT_FLTP, (const uint8_t *) data, _dataLen, 0);
    //        // printf("avcodec_fill_audio_frame ret:%d\n", ret);

    //        /*
    //        printf("====================================================\n");
    //        printf("Linesize 0:%d\n", p->frame->linesize[0]);
    //        printf("Linesize 1:%d\n", p->frame->linesize[1]);
    //        printf("Channels:%d\n", p->frame->channels);
    //        printf("nb_samples:%d\n", p->frame->nb_samples);
    //        printf("channel_layout:%lld\n", p->frame->channel_layout);
    //        printf("format:%lld\n", p->frame->format);
    //        */

    //        return 0;
    //    }
    //    return -1;
    //}
}
