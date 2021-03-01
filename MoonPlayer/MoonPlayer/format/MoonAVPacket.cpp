#include "MoonAVPacket.h"
#include "MoonAVPacketPrivate.h"

MoonAVPacket::MoonAVPacket()
{
    p = new MoonAVPacketPrivate();

    p->packet = av_packet_alloc();
    av_init_packet(p->packet);
}

MoonAVPacket::~MoonAVPacket()
{
    if (p->packet != nullptr) {
        av_packet_free(&p->packet);
        p->packet = nullptr;
    }

    if (p != nullptr) {
        delete p;
        p = nullptr;
    }
}

unsigned char* MoonAVPacket::GetDataPtr()
{
    return p->packet->data;
}

int MoonAVPacket::GetStreamId()
{
    return p->packet->stream_index;
}

uint64_t MoonAVPacket::GetPTS()
{
    return p->packet->pts;
}

double MoonAVPacket::GetSecPTS()
{
//    return p->ptsSec;
    return 0.0;
}

uint64_t MoonAVPacket::GetDTS()
{
    return p->packet->dts;
}
