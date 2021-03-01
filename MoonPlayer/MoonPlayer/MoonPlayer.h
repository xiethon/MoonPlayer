#pragma once

#include <iostream>
#include "format/MoonAVFormat.h"
#include "format/MoonAVPacket.h"

#include "video/MoonVideo.h"
#include "audio/MoonAudio.h"



class MoonPlayer
{
public:
	MoonPlayer();
	~MoonPlayer();
	
	int open(std::string url);
	int start();
	int stop();
	int seek();

	int getVideoDecode(MoonVideo* video);
	int getAudioDecode(MoonAudio* audio);

private:
	MoonAVFormat* format =nullptr;
	MoonVideo* video;
	MoonAudio* audio;
	
};

