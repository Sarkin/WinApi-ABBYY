#pragma once

#include "Component.h"
#include "Motion.h"

class CHead : public CComponent {
public:
    CHead();
    ~CHead();

    void Update();

    CMotion GetMotion() const;
    int GetLength() const;

private:
    CMotion motion_;
    int length_;
};

