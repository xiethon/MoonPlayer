#include "MoonAV.h"
#include "MoonAVReaderPrivate.h"
#include "MoonAVPacketPrivate.h"
#include "MoonAVStreamPrivate.h"

extern "C"{
#include <libavformat/avformat.h>
}


namespace Moon
{
    MoonAVReader::MoonAVReader(std::string _url)
    {
        p = new MoonAVReaderPrivate();
        p->url = _url;

        av_register_all();
        avformat_network_init();

        p->formatCtx = avformat_alloc_context();
    }

    MoonAVReader::~MoonAVReader()
    {
        if(p->formatCtx != NULL){
            close();
            avformat_free_context(p->formatCtx);
            p->formatCtx = NULL;
        }

        if(p != nullptr){
            delete p;
            p = nullptr;
        }
    }

    int MoonAVReader::getVideoStreamIndex()
    {
        if(p->formatCtx == nullptr){
            return -1;
        }

        int videoStream = av_find_best_stream(p->formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

        return videoStream;
    }

    int MoonAVReader::getAudioStreamIndex()
    {
        if(p->formatCtx == nullptr){
            return -1;
        }

        int audioStream = av_find_best_stream(p->formatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

        return audioStream;
    }

    int MoonAVReader::seekFrame(int streamIndex, double timestamp)
    {
        int64_t t = timestamp / av_q2d(p->formatCtx->streams[streamIndex]->time_base);
        return seekFrame(streamIndex, t);
    }

    int MoonAVReader::seekFrame(int streamIndex, int64_t timestamp)
    {
        if(p->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功
        /**
         * Seek to the keyframe at timestamp.
         * 'timestamp' in 'stream_index'.
         *
         * @param s media file handle
         * @param stream_index If stream_index is (-1), a default
         * stream is selected, and timestamp is automatically converted
         * from AV_TIME_BASE units to the stream specific time_base.
         * @param timestamp Timestamp in AVStream.time_base units
         *        or, if no stream is specified, in AV_TIME_BASE units.
         * @param flags flags which select direction and seeking mode
         * @return >= 0 on success
         */
        int ret = av_seek_frame(p->formatCtx, streamIndex, timestamp, AVSEEK_FLAG_BACKWARD);

        return ret;
    }

    int MoonAVReader::open()
    {
        int ret = avformat_open_input(&p->formatCtx, p->url.c_str(), NULL, NULL);
        if(ret){
            return -1;
        }

        avformat_find_stream_info(p->formatCtx, NULL);

        av_dump_format(p->formatCtx, 0, p->url.c_str(), 0);

        return 0;
    }

    int MoonAVReader::close()
    {
        avformat_close_input(&p->formatCtx);
        return 0;
    }

    int MoonAVReader::read(MoonAVPacket * packet)
    {
        int ret = av_read_frame(p->formatCtx, packet->p->packet);
        return ret;
    }

    int MoonAVReader::getStreamCount()
    {
        if(p->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功

        return p->formatCtx->nb_streams;
    }

    double MoonAVReader::getDuration()
    {
        return p->formatCtx->duration / 1000000;
    }

    int MoonAVReader::getStream(MoonAVStream & stream, int index)
    {
        if(p->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功
        if(index < 0){
            return -1;
        }
        if(index >= getStreamCount()) {
            return -1;
        }

        double duration = p->formatCtx->streams[index]->duration * 1.0 * p->formatCtx->streams[index]->time_base.num / p->formatCtx->streams[index]->time_base.den;
        stream.setDuration(duration);

        stream.streamIndex = p->formatCtx->streams[index]->index;
        stream.p->type = MoonAVStreamType::STREAM_TYPE_UNKNOW;

        avcodec_parameters_copy(stream.p->codecpar, p->formatCtx->streams[index]->codecpar);

        return 0;
    }

    int MoonAVReader::getStreamTimeBase(MoonAVRational & rational, int streamIndex)
    {
        if(streamIndex < 0){
            return -1;
        }
        if(streamIndex >= p->formatCtx->nb_streams){
            return -1;
        }

        rational.num = p->formatCtx->streams[streamIndex]->time_base.num;
        rational.den = p->formatCtx->streams[streamIndex]->time_base.den;

        return 0;
    }
}
