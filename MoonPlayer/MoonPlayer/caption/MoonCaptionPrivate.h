#pragma once

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


class MoonAVPacketPrivate
{
public:
    AVPacket* packet = nullptr;
};

