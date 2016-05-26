#include "Timer.h"



CTimer::CTimer(int timer) : timer_(timer) {
}


int CTimer::GetTimer() const {
    return timer_;
}

void CTimer::Update() {
    timer_--;
}