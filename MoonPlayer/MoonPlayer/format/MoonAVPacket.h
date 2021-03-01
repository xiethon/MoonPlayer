#pragma once
#include <iostream>
#include "../Moon.h"
class MoonAVPacketPrivate;

class MoonAVPacket
{
public:
	MoonAVPacket();
	~MoonAVPacket();

	inline MoonAVStreamType getStreamType(void) { return type; }//获取packet类型
	inline void setStreamType(MoonAVStreamType t) { type = t; } //设置packet 类型

	int GetStreamId();
	uint64_t GetPTS();
	double GetSecPTS();
	uint64_t GetDTS();
	unsigned char* GetDataPtr();

	MoonAVPacketPrivate* p = nullptr;

private:
	MoonAVStreamType type;
};

