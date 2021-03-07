#ifndef	Moon_AV_PACKET_PRIVATE_H
#define	Moon_AV_PACKET_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Moon
{
    class MoonAVPacketPrivate
    {
    public:
        AVPacket * packet = nullptr;
    };
}

#endif