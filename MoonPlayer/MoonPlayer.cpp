#include "MoonPlayer.h"
#include "MoonPlayerPrivate.h"

namespace Moon
{
	MoonPlayer::MoonPlayer()
	{
		p = new MoonPlayerPrivate();
	}

	MoonPlayer::~MoonPlayer()
	{
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
	}

	int MoonPlayer::open(std::string url)
	{
		p->url = url;

		readerThread = new MoonPlayerReaderThread(url);
		readerThread->start();
		return 0;
	}

	int MoonPlayer::start()
	{
		return 0;
	}

	int MoonPlayer::play()
	{
		return 0;
	}

	int MoonPlayer::pause()
	{
		return 0;
	}

	int MoonPlayer::stop()
	{
		if (readerThread != nullptr) 
		{
			readerThread->stop();
			delete readerThread;
			readerThread = nullptr;
		}
		return 0;
	}

	int MoonPlayer::seek(double time)
	{
		return 0;
	}
}