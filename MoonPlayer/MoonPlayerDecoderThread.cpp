#include "MoonPlayer.h"
#include "MoonAV/MoonAV.h"
#include<chrono>
#include<thread>


namespace Moon
{
	MoonPlayerDecoderThread::MoonPlayerDecoderThread()
	{
		decoder = new Moon::MoonAVDecoder();
	}

	MoonPlayerDecoderThread::~MoonPlayerDecoderThread()
	{
		if(decoder != nullptr)
		{
			delete decoder;
			decoder = nullptr;
		}
	}

	int MoonPlayerDecoderThread::init(MoonAVStream* avStream)
	{
		return decoder->init(avStream);
	}

	void MoonPlayerDecoderThread::run()
	{
		//½øĞĞ½âÂë
	}

}
