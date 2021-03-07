#pragma once

#include <iostream>
#include <mutex>
#include "format/MoonAVFormat.h"
#include "format/MoonAVPacket.h"

#include "video/MoonVideo.h"
#include "audio/MoonAudio.h"

class MoonPlayer
{
public:
	MoonPlayer();
	~MoonPlayer();
	
	int open(std::string url);	//打开
	int start();				//开始播放
	int stop();					//停止播放
	int seek(double pos);					//设置播放位置

	int getVideoDecode(MoonVideo* video);	//获取视频解码器
	int getAudioDecode(MoonAudio* audio);	//获取音频解码器
	int getVideoHeight();
	int getVideoWidth();
	double getDuration() { return totalMs; }	//获取总时长


private:
	int  read(MoonAVPacket* packet);	//读取流
	inline void setDuration(double ms) { totalMs = ms; }	//设置总时长
	void clear();	//清理format上下文
	void close();	//关闭format上下文
private:
	std::mutex mux;
	MoonAVFormat* format =nullptr;
	MoonVideo* video;
	MoonAudio* audio;
	double totalMs;
	int width = 0;
	int height = 0;
	
};

