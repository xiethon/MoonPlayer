#pragma once
#include "MoonAVPacketPrivate.h"
#include <iostream>

class MoonAVPacket
{
public:
	MoonAVPacket();
	~MoonAVPacket();

	int GetStreamId();
	uint64_t GetPTS();
	double GetSecPTS();
	uint64_t GetDTS();
	unsigned char* GetDataPtr();

	MoonAVPacketPrivate* p = nullptr;
};

