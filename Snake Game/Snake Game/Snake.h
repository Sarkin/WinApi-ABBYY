#pragma once

#include <Windows.h>

#include "Entity.h"
#include "Motion.h"

class CSnake : public CEntity {
public:
    CSnake(int x, int y, int player, std::map<WPARAM, Direction> key_mapping);
};

