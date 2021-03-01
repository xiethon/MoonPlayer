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

//����Ƶ
int MoonPlayer::open(std::string url)
{
	int ret =  format->open(url);

	//����򿪳ɹ����ȡ������
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
		//��ȡpacket
		int ret = format->read(packet);
		if (ret != 0) 
		{
			break;	//��ȡ���
		}

		int streamIndex = packet->p->packet->stream_index;

		if (streamIndex == format->getVideoStreamIndex())
		{
			std::cout << "ͼ��" << std::endl;
			//todo ͼ��packet����

		}
		if (streamIndex == format->getAudioStreamIndex()) 
		{
			std::cout << "��Ƶ" << std::endl;
			//todo ��Ƶpacket����
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