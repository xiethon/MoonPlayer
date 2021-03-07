#ifndef	MOON_AV_H
#define	MOON_AV_H

#include <iostream>
#include <vector>

namespace Moon
{
    class MoonAVReader;
    class MoonAVReaderPrivate;

	class MoonAVPacket;
	class MoonAVPacketPrivate;

	class MoonAVStream;
	class MoonAVStreamPrivate;

	class MoonAVDecoder;
	class MoonAVDecoderPrivate;

	class MoonAVFrame;
	class MoonAVFramePrivate;

	class MoonAVRational;

	enum MoonAVStreamType {
		STREAM_TYPE_UNKNOW = 0,
		STREAM_TYPE_AUDIO = 1,
		STREAM_TYPE_VIDEO = 2
	};

	enum MoonAVFormat
	{
		EYER_AV_SAMPLE_FMT_FLTP = 1
	};

	enum MoonAVAudioDateType
	{
		UNSIGNEDINT,
		SIGNEDINT,
		FLOAT
	};

	enum MoonAVPixelFormat
	{
		Moon_AV_PIX_FMT_UNKNOW = 0,
		Moon_AV_PIX_FMT_YUV420P = 101,
		Moon_AV_PIX_FMT_YUVJ420P = 102,
		Moon_AV_PIX_FMT_YUV444P = 103,
		Moon_AV_PIX_FMT_YUVJ444P = 104,
		Moon_AV_PIX_FMT_YUVNV12 = 105,
		Moon_AV_PIX_FMT_YUVNV21 = 106,
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

	class MoonAVDecoder
	{
	public:
		MoonAVDecoderPrivate* p = nullptr;
	public:
		MoonAVDecoder();
		~MoonAVDecoder();

		int init(MoonAVStream* stream);
		int initHW(MoonAVStream* stream);

		int sendPacket(MoonAVPacket* packet);
		int recvFrame(MoonAVFrame* frame);

		int getFrameSize();
		int getSampleRate();
	};

	class MoonAVFrame
	{
	public:
		MoonAVFramePrivate* p = nullptr;
		std::vector<void*> dataManager;
		int custom = 0;

		double timePts = 0.0;
	public:
		MoonAVFrame();
		~MoonAVFrame();

		MoonAVFrame(const MoonAVFrame& frame);
		MoonAVFrame& operator = (const MoonAVFrame& frame);

		int setPTS(int64_t pts);
		int64_t getPTS();

		int getYData(unsigned char* yData);
		int getUData(unsigned char* uData);
		int getVData(unsigned char* vData);
		int getUVData(unsigned char* uvData);

		float getAudioFloatData(int channel, int index);
		int setAudioFloatData(int channel, int index, float d);

		int getAudioPackedData(unsigned char* data);

		int getAudioData(unsigned char* data);
	//	int setAudioData(unsigned char* data, int dataLen, int nbSamples, int channel, MoonAVFormat format);

		int getLineSize(int channel);

		int setVideoData420P(unsigned char* y, unsigned char* u, unsigned char* v, int width, int height);

		int getWidth();
		int getHeight();

		int getChannels();
		int getNBSamples();
		int getPerSampleSize();
		int getSampleRate();
		MoonAVAudioDateType getAudioDateType();

		int initAACFrame(int channels);
		int getInfo();
		MoonAVPixelFormat getPixFormat() const;
	};
}

#endif
