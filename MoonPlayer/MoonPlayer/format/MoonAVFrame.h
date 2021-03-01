#pragma once
#include <iostream>
#include "../Moon.h"
class MoonAVFramePrivate;

class MoonAVFrame
{
public:
	MoonAVFrame();
	~MoonAVFrame();

	
	MoonAVFramePrivate* p = nullptr;

};

