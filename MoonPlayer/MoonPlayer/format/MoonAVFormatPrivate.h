#pragma once
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
}
class MoonAVFormatPrivate
{
public:
    AVFormatContext* formatCtx = nullptr;
};

