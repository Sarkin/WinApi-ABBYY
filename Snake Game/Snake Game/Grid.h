#pragma once

#include <vector>
#include <Windows.h>

class CGrid {
public:
    CGrid(int grid_h, int grid_w, int tile_sz);

    std::pair<int, int> GetGridSize();
    int GetTileSize();
    int Get(int x, int y) const;
    std::pair<int, int> GetFreeCell();

    std::pair<int, int> SpawnFood();
    std::pair<int, int> EatFood(int x, int y);

    void Draw(HDC hdc);

    void Add(int x, int y, int timer);
    void Add(std::pair<int, int> coords, int timer);

private:
    int grid_h_;
    int grid_w_;
    int tile_sz_;

    int getRandomUniform(int a, int b);

    std::vector<std::vector<int>> grid_;
};

