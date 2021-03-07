#include "MoonAV.h"
#include "MoonAVStreamPrivate.h"

namespace Moon
{
    MoonAVStream::MoonAVStream()
    {
        p = new MoonAVStreamPrivate();
        p->codecpar = avcodec_parameters_alloc();
    }
    
    MoonAVStream::~MoonAVStream()
    {
        if(p->codecpar != nullptr){
            avcodec_parameters_free(&p->codecpar);
            p->codecpar = nullptr;
        }
        if(p != nullptr){
            delete p;
            p = nullptr;
        }
    }

    MoonAVStreamType MoonAVStream::getStreamType()
    {
        if(p->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
            return MoonAVStreamType::STREAM_TYPE_VIDEO;
        }
        if(p->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
            return MoonAVStreamType::STREAM_TYPE_AUDIO;
        }

        return MoonAVStreamType::STREAM_TYPE_AUDIO;
    }

    int MoonAVStream::setDuration(double _duration)
    {
        duration = _duration;
        return 0;
    }

    double MoonAVStream::getDuration()
    {
        return duration;
    }

    int MoonAVStream::getWidth()
    {
        return p->codecpar->width;
    }

    int MoonAVStream::getHeight()
    {
        return p->codecpar->height;
    }
}
