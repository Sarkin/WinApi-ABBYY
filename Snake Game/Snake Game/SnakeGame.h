#pragma once

#include <Windows.h>
#include <vector>

#include "Snake.h"
#include "Grid.h"

class CSnakeGame {
public:
    CSnakeGame() { };
    CSnakeGame(HMODULE, HWND);

    void Update();

private:
    std::vector<CSnake> snakes;
    CGrid grid;
};