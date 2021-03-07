#ifndef	Moon_AV_FRAME_PRIVATE_H
#define	Moon_AV_FRAME_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
}

namespace Moon
{
    class MoonAVFramePrivate
    {
    public:
        AVFrame * frame = nullptr;
    };
}

#endif
