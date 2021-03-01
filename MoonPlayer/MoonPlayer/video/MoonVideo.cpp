#include "MoonVideo.h"
#include "MoonVideoCoderPrivate.h"
#include "../format/MoonAVPacketPrivate.h"
#include "../format/MoonAVFramePrivate.h"

MoonVideo::MoonVideo()
{
	p = new MoonVideoCoderPrivate();
}
MoonVideo::~MoonVideo()
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

void MoonVideo::close()
{
	if (p)
	{
		avcodec_close(p->codec);
		avcodec_free_context(&p->codec);
	}
}

void MoonVideo::clear()
{
	if (p)
		avcodec_flush_buffers(p->codec);
}

int MoonVideo::send(MoonAVPacket* pkt)
{
	if (!pkt || !p)
	{
		return -1;
	}
	if (! pkt->p->packet || !p->codec)
	{
		return -1;
	}
	int ret = avcodec_send_packet(p->codec, pkt->p->packet);
	av_packet_free(&pkt->p->packet);
	
	return ret;
}

int MoonVideo::recv(MoonAVFrame* frame)
{
	if (!frame || !p)
	{
		return -1;
	}
	if ( !p->codec)
	{
		return -1;
	}
	
	frame->p->frame = av_frame_alloc();
	int ret = avcodec_receive_frame(p->codec, frame->p->frame);
	if (ret != 0)
	{
		av_frame_free(&frame->p->frame);
		return -1;
	}

	std::cout << "VideoFrameLineSize:" << frame->p->frame->linesize[0] << std::endl;
	return 0;
}