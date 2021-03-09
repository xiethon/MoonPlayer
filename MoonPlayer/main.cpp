#include "MoonAV/MoonAV.h"
#include "MoonPlayer.h"
#include <iostream>
#include<chrono>
#include<thread>


int main(void)
{
	Moon::MoonPlayer player;
	
	player.open("C:\\Users\\DELL\\Desktop\\MoonPlayer\\bin\\debug\\test.mp4");

	player.start();


	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//	player.stop();

	getchar();

	return 0;

}




//int main(void)
//{
//	Moon::MoonPlayer player;
//	Moon::MoonAVReader reader("C:\\Users\\DELL\\Desktop\\MoonPlayer\\bin\\debug\\test.mp4");
//	int ret = reader.open();
//	if (ret != 0) {
//		return -1;
//	}
//	std::cout << "open success" << std::endl;
//
//	int streamCount = reader.getStreamCount();
//
//	Moon::MoonAVStream videoStream, audioStream;
//	reader.getStream(videoStream, 0);
//	reader.getStream(audioStream, 1);
//
//	Moon::MoonAVDecoder* videoDecoder = new Moon::MoonAVDecoder();
//	videoDecoder->init(&videoStream);
//
//	Moon::MoonAVDecoder* audioDecoder = new Moon::MoonAVDecoder();
//	audioDecoder->init(&audioStream);
//	while (1)
//	{
//		Moon::MoonAVPacket pkt;
//		ret = reader.read(&pkt);
//		if (ret)
//		{
//			break;
//		}
//
//		int streamIndex = pkt.getStreamId();
//		if (streamIndex == 0)
//		{
//			ret = videoDecoder->sendPacket(&pkt);
//			if (ret) {
//				continue;
//			}
//			while (1)
//			{
//				Moon::MoonAVFrame frame;
//				ret = videoDecoder->recvFrame(&frame);
//				if (ret)
//				{
//					break;
//				}
//				frame.getInfo();
//			}
//		}
//	}
//
//	reader.close();
//	getchar();
//	return 0;
//}