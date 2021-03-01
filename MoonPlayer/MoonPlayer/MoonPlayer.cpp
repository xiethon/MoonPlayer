#include "MoonPlayer.h"
#include <QDebug>


MoonPlayer::MoonPlayer()
{
	format = new MoonAVFormat();
	video = new MoonVideo();
	audio = new MoonAudio();
}

MoonPlayer::~MoonPlayer()
{
	if (format != nullptr)
	{
		delete format;
		format = nullptr;
	}
	if (video != nullptr)
	{
		delete video;
		video = nullptr;
	}
	if (audio != nullptr)
	{
		delete audio;
		audio = nullptr;
	}
}

int MoonPlayer::getAudioDecode(MoonAudio* audio)
{
	if (format == nullptr)
	{
		return -1;
	}
	return  format->getAudioCodec(audio);

}

int MoonPlayer::getVideoDecode(MoonVideo* video)
{
	if (format == nullptr)
	{
		return -1;
	}
	return  format->getVideoCodec(video);
	
}

//打开视频
int MoonPlayer::open(std::string url)
{
	int ret =  format->open(url);

	//如果打开成功则获取解码器
	if (ret == 0)
	{
		getVideoDecode(video);
		getAudioDecode(audio);
	}
	return ret;
}

int MoonPlayer::start()
{
	MoonAVPacket* packet = new MoonAVPacket();
	while (1)
	{
		//读取packet
		int ret = format->read(packet);
		if (ret != 0) 
		{
			break;	//读取完毕
		}

		int streamIndex = packet->p->packet->stream_index;

		if (streamIndex == format->getVideoStreamIndex())
		{
			std::cout << "图像" << std::endl;
			//todo 图像packet解码

		}
		if (streamIndex == format->getAudioStreamIndex()) 
		{
			std::cout << "音频" << std::endl;
			//todo 音频packet解码
		}
	}
	
	return 0;
}

int MoonPlayer::stop()
{
	return 0;
}

int MoonPlayer::seek()
{
	return 0;
}