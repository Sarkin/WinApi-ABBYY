#include "Grid.h"

#include <random>

#include "Draw.h"

CGrid::CGrid(int grid_h, int grid_w, int tile_sz) : grid_h_(grid_h), grid_w_(grid_w), tile_sz_(tile_sz),
    grid_(grid_h, std::vector<int>(grid_w, 0)) {
}

std::pair<int, int> CGrid::GetGridSize() {
    return std::make_pair(grid_h_, grid_w_);
}

int CGrid::GetTileSize() {
    return tile_sz_;
}

int CGrid::Get(int x, int y) const {
    return grid_[x][y];
}

std::pair<int, int> CGrid::SpawnFood() {
    std::pair<int, int> food_xy = GetFreeCell();
    grid_[food_xy.first][food_xy.second] = -1;
    return food_xy;
}

int CGrid::getRandomUniform(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

std::pair<int, int> CGrid::GetFreeCell() {
    std::vector<std::pair<int, int>> free_cells;
    for (int row = 2; row < grid_h_ - 2; row++) {
        for (int col = 2; col < grid_w_ - 2; col++) {
            if (grid_[row][col] == 0) {
                free_cells.push_back(std::make_pair(row, col));
            }
        }
    }
    return free_cells[getRandomUniform(0, free_cells.size() - 1)];
}

std::pair<int, int> CGrid::EatFood(int x, int y) {
    if (grid_[x][y] >= 0) {
        return std::make_pair(x, y);
    }
    Add(x, y, 1);
    return SpawnFood();
}

void CGrid::Draw(HDC hdc) {
    for (int row = 0; row < grid_h_; row++) {
        for (int col = 0; col < grid_w_; col++) {
            int y = (grid_w_ - col) * tile_sz_;
            int x = row * tile_sz_;
            if (grid_[row][col] > 0) {
                DrawTile(hdc, x, y, tile_sz_, RGB(150, 150, 255));
            }
            else if (grid_[row][col] == 0) {
                DrawTile(hdc, x, y, tile_sz_, RGB(0, 0, 0));
            }
            else {
                DrawTile(hdc, x, y, tile_sz_, RGB(255, 0, 0));
            }
        }
    }
}

void CGrid::Add(int x, int y, int timer) {
    grid_[x][y] += timer;
}

void CGrid::Add(std::pair<int, int> coords, int timer) {
    Add(coords.first, coords.second, timer);
}
