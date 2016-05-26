#pragma once

#include "Component.h"
#include "Motion.h"

class CHead : public CComponent {
public:
    CHead(int);

    int GetLength() const;
    void SetLength(int);

private:
    int length_;
};

