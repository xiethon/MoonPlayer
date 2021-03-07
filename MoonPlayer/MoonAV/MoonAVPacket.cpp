#include "MoonAV.h"
#include "MoonAVPacketPrivate.h"

extern "C"{
#include <libavformat/avformat.h>
}

namespace Moon
{
    MoonAVPacket::MoonAVPacket()
    {
        p = new MoonAVPacketPrivate();

        p->packet = av_packet_alloc();
        av_init_packet(p->packet);
    }

    MoonAVPacket::~MoonAVPacket()
    {
        if (p->packet != nullptr) {
            av_packet_free(&p->packet);
            p->packet = nullptr;
        }

        if(p != nullptr){
            delete p;
            p = nullptr;
        }
    }

    int MoonAVPacket::rescaleTs( Moon::MoonAVRational & _codecTimebase, Moon::MoonAVRational & _streamTimebase)
    {
        AVRational codecTimebase;
        codecTimebase.num = _codecTimebase.num;
        codecTimebase.den = _codecTimebase.den;

        AVRational streamTimebase;
        streamTimebase.num = _streamTimebase.num;
        streamTimebase.den = _streamTimebase.den;

        av_packet_rescale_ts(p->packet, codecTimebase, streamTimebase);
        return 0;
    }

    int MoonAVPacket::getStreamId()
    {
        return p->packet->stream_index;
    }

    uint64_t MoonAVPacket::getPTS()
    {
        return p->packet->pts;
    }

    uint64_t MoonAVPacket::getDTS()
    {
        return p->packet->dts;
    }

    int MoonAVPacket::setPTS(uint64_t pts)
    {
        p->packet->pts = pts;
        return 0;
    }
    
    int MoonAVPacket::setDTS(uint64_t dts)
    {
        p->packet->dts = dts;
        return 0;
    }

    int MoonAVPacket::setStreamId(int id)
    {
        p->packet->stream_index = id;
        return 0;
    }
}