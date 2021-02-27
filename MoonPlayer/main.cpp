extern "C" {
	#include "libavformat/avformat.h"
	#include "libavcodec/avcodec.h"
	#include "libswscale/swscale.h"
	#include "libswresample/swresample.h"
}
#include <stdio.h>

int main()
{
	av_register_all();//³õÊ¼»¯·â×°¿â
	return 0;
}