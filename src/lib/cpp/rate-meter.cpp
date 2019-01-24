#include "rate-meter.hpp"

using namespace std::chrono;

RateMeter::RateMeter():
rate(0),
lastSampleSystemClock(system_clock::now()) {
}

void RateMeter::updateRate() {
    time_point<system_clock> now = system_clock::now();
    std::chrono::duration<double> difference = now - lastSampleSystemClock;
    lastSampleSystemClock = now;
    
    double count = difference.count();
    if (count == 0) {
        rate = 0;
    } else {
        rate = 1 / difference.count();
    }
}

double RateMeter::getRate() {
    return rate;
}
