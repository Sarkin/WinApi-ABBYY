#include "Grid.h"

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

void CGrid::Add(std::pair<int, int> coords, int timer) {
    grid_[coords.first][coords.second] += timer;
}
