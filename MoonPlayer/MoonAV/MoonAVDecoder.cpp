#include "MoonAV.h"

#include "MoonAVStreamPrivate.h"
#include "MoonAVDecoderPrivate.h"
#include "MoonAVPacketPrivate.h"
#include "MoonAVFramePrivate.h"



namespace Moon
{
    MoonAVDecoder::MoonAVDecoder()
    {
        p = new MoonAVDecoderPrivate();
        p->codecContext = avcodec_alloc_context3(nullptr);
    }

    MoonAVDecoder::~MoonAVDecoder()
    {
        if(p->codecContext != nullptr){
            avcodec_free_context(&p->codecContext);
            p->codecContext = nullptr;
        }
        if(p != nullptr){
            delete p;
            p = nullptr;
        }
    }

    int MoonAVDecoder::initHW(MoonAVStream * stream)
    {
        avcodec_parameters_to_context(p->codecContext, stream->p->codecpar);
        AVCodec * codec = avcodec_find_decoder(p->codecContext->codec_id);


        int ret = avcodec_open2(p->codecContext, codec, nullptr);
        if(ret){
            std::cout<<"Open Decoder Fail\n"<<std::endl;
            return -1;
        }

        return 0;
    }

    int MoonAVDecoder::init(MoonAVStream * stream)
    {
        avcodec_parameters_to_context(p->codecContext, stream->p->codecpar);

        AVCodec * codec = avcodec_find_decoder(p->codecContext->codec_id);

        p->codecContext->thread_count = 4;

        int ret = avcodec_open2(p->codecContext, codec, nullptr);
        if(ret){
            std::cout << "Open Decoder Fail\n" << std::endl;
            return -1;
        }
        return 0;
    }

    int MoonAVDecoder::getFrameSize()
    {
        return p->codecContext->frame_size;
    }

    int MoonAVDecoder::getSampleRate()
    {
        return p->codecContext->sample_rate;
    }

    int MoonAVDecoder::sendPacket(MoonAVPacket * packet)
    {
        // TODO 判断解码器是否打开
        AVPacket * avpkt = nullptr;
        if(packet != nullptr){
            avpkt = packet->p->packet;
        }

        int ret = avcodec_send_packet(p->codecContext, avpkt);
        return ret;
    }

    int MoonAVDecoder::recvFrame(MoonAVFrame * frame)
    {
        int ret = avcodec_receive_frame(p->codecContext, frame->p->frame);
        return ret;
    }
}
