#pragma once

#include "Component.h"
#include "Motion.h"

class CBody : public  CComponent {
public:
    CBody();
    ~CBody();

    void Update();
    
private:
    CMotion motion_;
    int timer_;
};

