#pragma once

#include "Entity.h"
#include "Motion.h"

class CBody : public  CEntity {
public:
    CBody();
    CBody(CMotion motion, int timer);
    ~CBody();

    void Update();
    
private:
    CMotion motion_;
    int timer_;
};

