#include "SnakeGame.h"

#include "Trail.h"
#include "Decay.h"

CSnakeGame::CSnakeGame(int grid_h, int grid_w) : grid_(grid_h, grid_w, 10) {
    em_.Add(std::unique_ptr<CEntity>(new CSnake(grid_h / 2, grid_w / 3, 0)));
    Trail::Run(em_, *this);
}

void CSnakeGame::Update() {
    Decay::Run(em_, *this);
    for (auto it = em_.begin(); it != em_.end(); it++) {
        (*it)->Update();
    }
    Trail::Run(em_, *this);
}

void CSnakeGame::Draw(HDC hdc) {
    grid_.Draw(hdc);
}

std::pair<int, int> CSnakeGame::GetGridSize() {
    return grid_.GetGridSize();
}

int CSnakeGame::GetTileSize() {
    return grid_.GetTileSize();
}

CGrid& CSnakeGame::GetGrid() {
    return grid_;
}