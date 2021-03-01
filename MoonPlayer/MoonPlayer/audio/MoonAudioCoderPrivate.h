#pragma once

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


class MoonAudioCoderPrivate
{
public:
    AVCodecContext* codec = nullptr;
};

