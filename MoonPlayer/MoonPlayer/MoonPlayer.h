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
	
	int open(std::string url);	//��
	int start();				//��ʼ����
	int stop();					//ֹͣ����
	int seek(double pos);					//���ò���λ��

	int getVideoDecode(MoonVideo* video);	//��ȡ��Ƶ������
	int getAudioDecode(MoonAudio* audio);	//��ȡ��Ƶ������
	int getVideoHeight();
	int getVideoWidth();
	double getDuration() { return totalMs; }	//��ȡ��ʱ��


private:
	int  read(MoonAVPacket* packet);	//��ȡ��
	inline void setDuration(double ms) { totalMs = ms; }	//������ʱ��
	void clear();	//����format������
	void close();	//�ر�format������
private:
	std::mutex mux;
	MoonAVFormat* format =nullptr;
	MoonVideo* video;
	MoonAudio* audio;
	double totalMs;
	int width = 0;
	int height = 0;
	
};

