#pragma once
#include <iostream>
#include "MoonAVFormatPrivate.h"
#include "../video/MoonVideo.h"
#include "../audio/MoonAudio.h"
#include "MoonAVPacket.h"

class MoonAVFormat
{
public:
	MoonAVFormat();
	~MoonAVFormat();

	int open(std::string url);
	int read(MoonAVPacket* packet);
	int close();
	double getDuration();

	int getAudioStreamIndex();
	int getVideoStreamIndex();
	int getVideoCodec(MoonVideo* video);
	int getAudioCodec(MoonAudio* audio);

private:
	MoonAVFormatPrivate* p = nullptr;
	std::string url;
};

