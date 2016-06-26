#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED

#include <chrono>
#include <thread>

class FrameCap
{
private:
    float min_time, delay;
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;

public:
    FrameCap (const float fps) : min_time (1e6f / fps), delay (0), t1 (std::chrono::high_resolution_clock::now() ) {}

    void limit()
    {
        t2 = std::chrono::high_resolution_clock::now();
        delay = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        if (delay <= min_time)
            std::this_thread::sleep_for (std::chrono::microseconds(static_cast<unsigned>(min_time - delay)));

        t1 = std::chrono::high_resolution_clock::now();
    }

    void setFPS (const float fps) { min_time = 1e6f / fps; }
};

#endif // FPS_HPP_INCLUDED
