#pragma once
#include <iostream>

class MoonAudioCoderPrivate;

class MoonAudio
{
public:
	MoonAudio();
	~MoonAudio();
	void clear();
	void close();

	MoonAudioCoderPrivate* p;
};

