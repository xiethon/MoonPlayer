#include "MoonPlayer.h"
#include "MoonAV/MoonAV.h"
#include<chrono>
#include<thread>


namespace Moon
{
	MoonPlayerReaderThread::MoonPlayerReaderThread(std::string _url):url(_url)
	{
	
	}

	MoonPlayerReaderThread::~MoonPlayerReaderThread()
	{
	
	}

	void MoonPlayerReaderThread::run()
	{
		Moon::MoonAVReader reader(url);
		int ret = reader.open();
		{
			if(ret != 0)
			{
				std::cout << "open failed!" << std::endl;
				return;
			}
		}

		int videoIndex = reader.getVideoStreamIndex();
		int audioIndex = reader.getAudioStreamIndex();

		MoonPlayerDecoderThread* videoDecoderThread = new MoonPlayerDecoderThread();
		MoonPlayerDecoderThread* audioDecoderThread = new MoonPlayerDecoderThread();
		//初始化解码器
		MoonAVStream videoStream, audioStream;
		ret = reader.getStream(videoStream,videoIndex);
		if(ret != 0)
		{
			videoDecoderThread->init(&videoStream);
		}

		ret = reader.getStream(audioStream, audioIndex);
		if (ret != 0)
		{
			audioDecoderThread->init(&audioStream);
		}
		
		videoDecoderThread->start();
		audioDecoderThread->start();
		//读流
		while(isRunning())
		{
			Moon::MoonAVPacket* pkt = new Moon::MoonAVPacket();
			int ret = reader.read(pkt);
			if(ret)
			{
				delete pkt;
				pkt = nullptr;
				break;
			}

			if(pkt->getStreamIndex() == videoIndex)
			{
				std::cout << "视频流" << std::endl;
			}
			else if(pkt->getStreamIndex() == audioIndex)
			{
				std::cout << "音频流" << std::endl;
			}

			//将packet放入缓存
			delete pkt;
			pkt = nullptr;

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}

		videoDecoderThread->stop();
		audioDecoderThread->stop();
		delete videoDecoderThread;
		delete audioDecoderThread;
	}

}
