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

//打开视频
int MoonPlayer::open(std::string url)
{
	close();
	mux.lock();
	int ret =  format->open(url);

	//如果打开成功则获取解码器
	if (ret == 0)
	{
		getVideoDecode(video);
		getAudioDecode(audio);
		setDuration(format->getDuration());	//获取总时长
	}
	mux.unlock();
	return ret;
}

int MoonPlayer::start()
{
	MoonAVPacket* packet = new MoonAVPacket();
	while (1)
	{
		//读取数据流
		int ret = read(packet); 
		if (ret != 0) 
		{
			break;	//读取完毕
		}

		//根据数据流类型解码数据
		MoonAVStreamType type = packet->getStreamType();
		if (type == MoonAVStreamType::STREAM_TYPE_VIDEO)
		{
			std::cout << "图像" << std::endl;
			//todo 图像packet解码
			video->send(packet);
			MoonAVFrame* frame = new MoonAVFrame();
			video->recv(frame);
		}
		else if (type == MoonAVStreamType::STREAM_TYPE_AUDIO)
		{
			std::cout << "音频" << std::endl;
			//todo 图像packet解码
		}
		
	}
	
	return 0;
}

//读取数据流
int MoonPlayer::read(MoonAVPacket* packet)
{
	mux.lock();
	//读取packet
	int ret =  format->read(packet);
	mux.unlock();
	return ret;
}

void MoonPlayer::clear()
{
	mux.lock();
	if (format)
	{
		format->clear(); //清理format上下文
	}
	//清理读取缓冲
	
	if (video)
	{
		video->clear();
	}
	mux.unlock();
}

void MoonPlayer::close()	//关闭format上下文
{
	mux.lock();
	if (format)
	{
		format->close(); //清理format上下文
	}
	if (video)
	{
		video->close(); //清理video上下文
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
	//清理读取缓冲
	format->clear();

	double seekPos = getDuration() * pos;
	int ret = format->seek(seekPos);
	mux.unlock();
	return ret;
}