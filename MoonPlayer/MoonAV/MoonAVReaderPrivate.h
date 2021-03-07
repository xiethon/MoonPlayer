#ifndef	MOON_AV_READER_PRIVATE_H
#define	MOON_AV_READER_PRIVATE_H

#include "MoonAV.h"

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Moon
{
    class MoonAVReaderPrivate
    {
    public:
        std::string url;
        AVFormatContext * formatCtx = nullptr;
    };
}

#endif