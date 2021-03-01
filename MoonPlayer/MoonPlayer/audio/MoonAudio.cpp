#include "MoonAudio.h"
#include "MoonAudioCoderPrivate.h"

MoonAudio::MoonAudio()
{
	p = new MoonAudioCoderPrivate();
}

MoonAudio::~MoonAudio()
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

//ÇåÀíAudio
void MoonAudio::clear()
{
	if (p)
		avcodec_flush_buffers(p->codec);
}

void MoonAudio::close()
{
	if (p)
	{
		avcodec_close(p->codec);
		avcodec_free_context(&p->codec);
	}
}