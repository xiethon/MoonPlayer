#include "MoonAVFormat.h"
#include "MoonAVFormatPrivate.h"
#include "MoonAVPacketPrivate.h"
#include "../audio/MoonAudioCoderPrivate.h"
#include "../video/MoonVideoCoderPrivate.h"
#include "../Moon.h"

#include <QDebug>

static double r2d(AVRational r)
{
    return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}


MoonAVFormat::MoonAVFormat()
{
    p = new MoonAVFormatPrivate();
    av_register_all();
    avformat_network_init();
    p->formatCtx = avformat_alloc_context();
}

MoonAVFormat::~MoonAVFormat()
{
    if (p->formatCtx != NULL) {
        avformat_free_context(p->formatCtx);
        p->formatCtx = NULL;
    }

    if (p != nullptr) {
        delete p;
        p = nullptr;
    }
}

//打开视频
int MoonAVFormat::open(std::string url)
{
    int ret = avformat_open_input(&p->formatCtx, url.c_str(), NULL, NULL);
    if (ret) {
        return -1;
    }
    avformat_find_stream_info(p->formatCtx, NULL);
    av_dump_format(p->formatCtx, 0, url.c_str(), 0);
    return 0;
}

//获取视频解码器
int MoonAVFormat::getVideoCodec(MoonVideo* video)
{
    if (video == nullptr)
    {
        return -1;
    }
    int videoStreamIndex = getVideoStreamIndex();
    if (videoStreamIndex != -1)
    {
        //找到视频解码器
        AVCodec* vcodec = avcodec_find_decoder(p->formatCtx->streams[videoStreamIndex]->codecpar->codec_id);
        if (!vcodec)
        {
            std::cout << " VideoCoder:find error" << std::endl;
            return -1;
        }
        AVCodecContext* ac = avcodec_alloc_context3(vcodec);
        avcodec_parameters_to_context(ac, p->formatCtx->streams[videoStreamIndex]->codecpar);
        ac->thread_count = 8;
        int ret = avcodec_open2(ac, 0, 0);
        if (ret != 0)
        {
            avcodec_free_context(&video->p->codec);
            std::cout << "video avcodec_open2 error" << std::endl;
            return -1;
        }
        video->p->codec = ac;
        return 0;
    }
}

//获取音频解码器
int MoonAVFormat::getAudioCodec(MoonAudio* audio)
{
    if (audio == nullptr)
    {
        return -1;
    }
    int index = getAudioStreamIndex();
    if (index != -1)
    {
        //找到视频解码器
        AVCodec* vcodec = avcodec_find_decoder(p->formatCtx->streams[index]->codecpar->codec_id);
        if (!vcodec)
        {
            std::cout << " AudioCoder:find error" << std::endl;
            return -1;
        }
        AVCodecContext* ac = avcodec_alloc_context3(vcodec);
        avcodec_parameters_to_context(ac, p->formatCtx->streams[index]->codecpar);
        ac->thread_count = 8;
        int ret = avcodec_open2(ac, 0, 0);
        if (ret != 0)
        {
            std::cout << "video avcodec_open2 error" << std::endl;
            return -1;
        }
        audio->p->codec = ac;
        return 0;
    }
}

//关闭视频
int MoonAVFormat::close()
{
    avformat_close_input(&p->formatCtx);
    return 0;
}

void MoonAVFormat::clear()
{
    avformat_flush(p->formatCtx);
}

//读取视频
int MoonAVFormat::read(MoonAVPacket* packet)
{
    if (p->formatCtx == nullptr || packet == nullptr)
    {
        return -1;
    }

    AVPacket* pkt = av_packet_alloc();

    int ret = av_read_frame(p->formatCtx, pkt);
    if (ret == 0)
    {
        pkt->pts = pkt->pts * (1000 * (r2d(p->formatCtx->streams[pkt->stream_index]->time_base)));  //单位转换为ms
        pkt->dts = pkt->dts * (1000 * (r2d(p->formatCtx->streams[pkt->stream_index]->time_base)));  //单位转换为ms
        packet->p->packet = pkt;
       
        if (packet->p->packet->stream_index == getVideoStreamIndex())
        {
            packet->setStreamType(MoonAVStreamType::STREAM_TYPE_VIDEO);
        }
        else if (packet->p->packet->stream_index == getAudioStreamIndex())
        {
            packet->setStreamType(MoonAVStreamType::STREAM_TYPE_AUDIO);
        }
        else 
        {
            packet->setStreamType(MoonAVStreamType::STREAM_TYPE_UNKNOW);
        }
        return 0;
    }
    else 
    {
        av_packet_free(&pkt);
        return -1;
    }
}

//设置播放位置
int MoonAVFormat::seek(double pos)					
{
    return av_seek_frame(p->formatCtx, getVideoStreamIndex(), pos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
}

double MoonAVFormat::getDuration()
{
    return p->formatCtx->duration / (AV_TIME_BASE / 1000);
}

//获取音频流 stream index
//返回 -1 为失败
int MoonAVFormat::getAudioStreamIndex()
{
    if (p->formatCtx == nullptr) {
        return -1;
    }

    int index = av_find_best_stream(p->formatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    return index;
}

//获取视频流 stream index
//返回 -1 为失败
int MoonAVFormat::getVideoStreamIndex()
{
    if (p->formatCtx == nullptr) {
        return -1;
    }

    int index = av_find_best_stream(p->formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    return index;
}