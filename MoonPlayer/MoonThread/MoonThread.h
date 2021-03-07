#ifndef	MOON_THREAD_H
#define	MOON_THREAD_H

#include <thread>
#include <mutex>
#include <atomic>

namespace Moon
{
    class MoonThread
    {
    public:
        MoonThread();
        ~MoonThread();

        virtual void run() = 0;

        int stop(int t = 1000);

        int isRunning();
        int start();

    protected:
        void setRunning();
        void setStoping();

        std::atomic_int stopFlag {0};
        std::atomic_int isRun {0};

    private:
        std::thread * t = nullptr;
    };
}

#endif