#pragma once

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


class MoonVideoCoderPrivate
{
public:
    AVCodecContext* coder = nullptr;
};

