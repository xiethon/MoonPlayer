#ifndef	MOON_AV_H
#define	MOON_AV_H

#include <iostream>

namespace Moon
{
    class MoonAVReader;
    class MoonAVReaderPrivate;

	class MoonAVPacket;
	class MoonAVPacketPrivate;

	class MoonAVStream;
	class MoonAVStreamPrivate;

	class MoonAVRational;

	enum MoonAVStreamType {
		STREAM_TYPE_UNKNOW = 0,
		STREAM_TYPE_AUDIO = 1,
		STREAM_TYPE_VIDEO = 2
	};

	class MoonAVStream
	{
	public:
		int streamIndex = -1;
		MoonAVStreamPrivate* p = nullptr;

		double duration = 0;
	public:
		MoonAVStream();
		~MoonAVStream();

		MoonAVStreamType getStreamType();

		int setDuration(double _duration);
		double getDuration();

		int getWidth();
		int getHeight();
	};

	class MoonAVPacket
	{
	public:
		MoonAVPacketPrivate* p = nullptr;
	public:
		MoonAVPacket();
		~MoonAVPacket();

		int getStreamId();

		uint64_t getPTS();
		uint64_t getDTS();

		int rescaleTs(Moon::MoonAVRational& codecTimebase, Moon::MoonAVRational& streamTimebase);

		int setPTS(uint64_t pts);
		int setDTS(uint64_t dts);

		int setStreamId(int id);
	};

    class MoonAVReader
    {
    public:
        MoonAVReaderPrivate * p = nullptr;
    public:
        MoonAVReader(std::string _url);
        ~MoonAVReader();

        int open();
        int close();

        double getDuration();

		int seekFrame(int streamIndex, int64_t timestamp);
		int seekFrame(int streamIndex, double timestamp);

        int read(MoonAVPacket * packet);

        int getStreamCount();
        int getStream(MoonAVStream & stream, int index);

        int getAudioStreamIndex();
        int getVideoStreamIndex();

        int getStreamTimeBase(MoonAVRational& rational, int streamIndex);
    };

	class MoonAVRational
	{
	public:
		int num = 0;
		int den = 0;

		MoonAVRational();
		MoonAVRational(const MoonAVRational& avRational);
		~MoonAVRational();

		MoonAVRational& operator = (const MoonAVRational& avRational);
	};
}

#endif
