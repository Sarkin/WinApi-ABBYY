#pragma once

#include <vector>
#include <Windows.h>

class CGrid {
public:
    CGrid(int grid_h, int grid_w, int tile_sz);

    std::pair<int, int> GetGridSize();
    int GetTileSize();

    void Draw(HDC hdc);

    void Add(std::pair<int, int> coords, int timer);

private:
    int grid_h_;
    int grid_w_;
    int tile_sz_;

    std::vector<std::vector<int>> grid_;
};

