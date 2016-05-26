#pragma once

#include "Component.h"

class CPlayerControlled : public CComponent {
public:
    CPlayerControlled(int player);

    int GetPlayer() const;

private:
    int player_;
};

