#pragma once
#include <iostream>
#include "MoonVideoCoderPrivate.h"

class MoonVideo
{
public:
	MoonVideo();
	~MoonVideo();

	MoonVideoCoderPrivate* coder;
};

