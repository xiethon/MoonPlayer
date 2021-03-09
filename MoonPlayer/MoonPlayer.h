#ifndef	MOON_PLAYER_H
#define	MOON_PLAYER_H

#include <iostream>
#include "MoonThread/MoonThread.h"
#include "MoonAV/MoonAV.h"

namespace Moon {
	
	class MoonPlayerPrivate;
	class MoonPlayerReaderThread;
	class MoonPlayerDecoderThread;
	
	class MoonPlayer
	{
	public:
		MoonPlayer();
		~MoonPlayer();

		int open(std::string url);
		int start();
		int play();
		int pause();
		int stop();
		int seek(double time);
	private:
		MoonPlayerPrivate* p = nullptr;
		MoonPlayerReaderThread* readerThread = nullptr;
		MoonPlayerDecoderThread* decoderThread = nullptr;
	};

	class MoonPlayerReaderThread : public MoonThread
	{
	public:
		MoonPlayerReaderThread(std::string _url);
		~MoonPlayerReaderThread();

		virtual void run();

	private:
		std::string url;
	};

	class MoonPlayerDecoderThread : public MoonThread
	{
	public:
		MoonPlayerDecoderThread();
		~MoonPlayerDecoderThread();

		virtual void run();
		int init(MoonAVStream* avStream);

	private:
		MoonAVDecoder* decoder = nullptr;
	};
}

#endif