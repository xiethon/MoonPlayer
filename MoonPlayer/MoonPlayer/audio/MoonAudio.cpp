#include "MoonAudio.h"

MoonAudio::MoonAudio()
{
	coder = new MoonAudioCoderPrivate();
}
MoonAudio::~MoonAudio()
{
	if (coder != nullptr)
	{
		delete coder;
		coder = nullptr;
	}
}