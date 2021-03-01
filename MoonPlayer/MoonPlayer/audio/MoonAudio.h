#pragma once
#include <iostream>
#include "MoonAudioCoderPrivate.h"

class MoonAudio
{
public:
	MoonAudio();
	~MoonAudio();

	MoonAudioCoderPrivate* coder;
};

