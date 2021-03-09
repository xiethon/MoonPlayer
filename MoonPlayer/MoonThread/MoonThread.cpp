#include "MoonThread.h"

namespace Moon
{
    MoonThread::MoonThread()
    {

    }

    MoonThread::~MoonThread()
    {
        stop();
    }

    int MoonThread::stop(int time)
    {
        if(t == nullptr){
            return -1;
        }

        setStoping();
        if(t != nullptr){
            t->join();
            delete t;
            t = nullptr;
        }
        return 0;
    }

    int MoonThread::isRunning()
    {
        return isRun;
    }

    int MoonThread::start()
    {
        if(t != nullptr){
            return -1;
        }

        setRunning();
        t = new std::thread(&MoonThread::run, this);

        return 0;
    }

    void MoonThread::setRunning()
    {
        stopFlag = 0;
        isRun = 1;
    }

    void MoonThread::setStoping()
    {
        stopFlag = 1;
        isRun = 0;
    }
}