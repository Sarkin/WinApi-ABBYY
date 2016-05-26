#pragma once

#include "Component.h"

class CTimer : public CComponent {
public:
    CTimer(int);
    
    int GetTimer() const;

    void Update();

private:
    int timer_;
};

