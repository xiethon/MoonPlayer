#include "MoonAVFrame.h"
#include "MoonAVFramePrivate.h"

MoonAVFrame::MoonAVFrame()
{
    p = new MoonAVFramePrivate();
}

MoonAVFrame::~MoonAVFrame()
{
    if (p->frame != nullptr) {
        av_frame_free(&p->frame);
        p->frame = nullptr;
    }

    if (p != nullptr) {
        delete p;
        p = nullptr;
    }
}
