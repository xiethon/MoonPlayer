#include "MoonAV.h"

namespace Moon
{
    MoonAVRational::MoonAVRational()
    {
        num = 0;
        den = 0;
    }

    MoonAVRational::MoonAVRational(const MoonAVRational & avRational)
    {
        *this = avRational;
    }

    MoonAVRational::~MoonAVRational()
    {

    }

    MoonAVRational & MoonAVRational::operator = (const MoonAVRational & avRational)
    {
        num = avRational.num;
        den = avRational.den;

        return *this;
    }
}