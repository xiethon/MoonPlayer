#include "MoonPlayer.h"
#include "Moon.h"
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
	close();
	mux.lock();
	int ret =  format->open(url);

	//����򿪳ɹ����ȡ������
	if (ret == 0)
	{
		getVideoDecode(video);
		getAudioDecode(audio);
		setDuration(format->getDuration());	//��ȡ��ʱ��
	}
	mux.unlock();
	return ret;
}

int MoonPlayer::start()
{
	MoonAVPacket* packet = new MoonAVPacket();
	while (1)
	{
		//��ȡ������
		int ret = read(packet); 
		if (ret != 0) 
		{
			break;	//��ȡ���
		}

		//�������������ͽ�������
		MoonAVStreamType type = packet->getStreamType();
		if (type == MoonAVStreamType::STREAM_TYPE_VIDEO)
		{
			std::cout << "ͼ��" << std::endl;
			//todo ͼ��packet����
			video->send(packet);
			MoonAVFrame* frame = new MoonAVFrame();
			video->recv(frame);
		}
		else if (type == MoonAVStreamType::STREAM_TYPE_AUDIO)
		{
			std::cout << "��Ƶ" << std::endl;
			//todo ͼ��packet����
		}
		
	}
	
	return 0;
}

//��ȡ������
int MoonPlayer::read(MoonAVPacket* packet)
{
	mux.lock();
	//��ȡpacket
	int ret =  format->read(packet);
	mux.unlock();
	return ret;
}

void MoonPlayer::clear()
{
	mux.lock();
	if (format)
	{
		format->clear(); //����format������
	}
	//�����ȡ����
	
	if (video)
	{
		video->clear();
	}
	mux.unlock();
}

void MoonPlayer::close()	//�ر�format������
{
	mux.lock();
	if (format)
	{
		format->close(); //����format������
	}
	if (video)
	{
		video->close(); //����video������
	}
	
	mux.unlock();
}

int MoonPlayer::stop()
{
	return 0;
}

int MoonPlayer::seek(double pos)
{
	mux.lock();
	if (!format)
	{
		mux.unlock();
		return false;
	}
	//�����ȡ����
	format->clear();

	double seekPos = getDuration() * pos;
	int ret = format->seek(seekPos);
	mux.unlock();
	return ret;
}