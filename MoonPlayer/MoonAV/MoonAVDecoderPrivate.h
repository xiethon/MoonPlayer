#ifndef	MOON_AV_DECODER_PRIVATE_H
#define	MOON_AV_DECODER_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
}

namespace Moon
{
    class MoonAVDecoderPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
        int isHW = 0;
    };
}

#endif