#pragma once

#include <Windows.h>
#include <vector>

#include "Snake.h"
#include "Grid.h"

class CSnakeGame {
public:
    CSnakeGame(int grid_h, int grid_w);

    void Update();
    void Draw(HDC);

    CGrid& GetGrid();
    std::pair<int, int> GetGridSize();
    int GetTileSize();

private:
    CGrid grid_;
    EntityManager em_;
};