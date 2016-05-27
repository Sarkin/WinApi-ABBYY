#pragma once

#include <map>
#include <Windows.h>

#include "Component.h"
#include "Motion.h"

class CPlayerControlled : public CComponent {
public:
    CPlayerControlled(int player, std::map<WPARAM, Direction> key_mapping);

    int GetPlayer() const;
    bool HandleInput(WPARAM wParam);

private:
    int player_;
    std::map<WPARAM, Direction> key_mapping_;
};

