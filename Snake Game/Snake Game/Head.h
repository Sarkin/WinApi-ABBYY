#pragma once

#include "Component.h"
#include "Motion.h"

class CHead : public CComponent {
public:
    CHead();
    ~CHead();

    void Update();

private:
    CMotion motion_;
    int length_;
};

