#include "MoonVideo.h"

MoonVideo::MoonVideo()
{
	coder = new MoonVideoCoderPrivate();
}
MoonVideo::~MoonVideo()
{
	if (coder != nullptr)
	{
		delete coder;
		coder = nullptr;
	}
}