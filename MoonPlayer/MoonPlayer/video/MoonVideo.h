#pragma once
#include <iostream>
#include "../format/MoonAVPacket.h"
#include "../format/MoonAVFrame.h"

class MoonVideoCoderPrivate;
class MoonVideo
{
public:
	MoonVideo();
	~MoonVideo();
	void clear();
	void close();
	int send(MoonAVPacket* packet);
	int recv(MoonAVFrame* frame);
	int getHeight();
	int getWidth();
	MoonVideoCoderPrivate* p;
};

