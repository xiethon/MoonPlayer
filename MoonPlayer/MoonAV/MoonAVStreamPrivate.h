#ifndef	MOON_AV_STREAM_PRIVATE_H
#define	MOON_AV_STREAM_PRIVATE_H

#include "MoonAV.h"

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Moon
{
    class MoonAVStreamPrivate
    {
    public:
        AVCodecParameters * codecpar = nullptr;
        MoonAVStreamType type = MoonAVStreamType::STREAM_TYPE_UNKNOW;
    };
}


#endif