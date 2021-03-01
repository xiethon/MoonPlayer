#pragma once
#include <iostream>
#include "../video/MoonVideo.h"
#include "../audio/MoonAudio.h"
#include "MoonAVPacket.h"

class MoonAVFormatPrivate;

class MoonAVFormat
{
public:
	MoonAVFormat();
	~MoonAVFormat();

	int open(std::string url);
	int read(MoonAVPacket* packet);
	int close();
	void clear();
	int seek(double pos);					//…Ë÷√≤•∑≈Œª÷√

	double getDuration();

	int getAudioStreamIndex();
	int getVideoStreamIndex();
	int getVideoCodec(MoonVideo* video);
	int getAudioCodec(MoonAudio* audio);

private:
	MoonAVFormatPrivate* p = nullptr;
	std::string url;
};

