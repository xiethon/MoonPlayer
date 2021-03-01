#pragma once

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


class MoonAVFramePrivate
{
public:
    AVFrame* frame = nullptr;
};

