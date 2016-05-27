#include "SnakeGame.h"

#include "Trail.h"
#include "Decay.h"
#include "Collision.h"
#include "Food.h"
#include "PlayerControlled.h"
#include "Input.h"

CSnakeGame::CSnakeGame(int grid_h, int grid_w) : grid_(grid_h, grid_w, 10) {
    std::map<WPARAM, Direction> player1;
    player1[VK_UP] = Direction::Up;
    player1[VK_DOWN] = Direction::Down;
    player1[VK_RIGHT] = Direction::Right;
    player1[VK_LEFT] = Direction::Left;
    em_.Add(std::unique_ptr<CEntity>(new CSnake(grid_h / 2, grid_w / 3, 0, player1)));
    std::map<WPARAM, Direction> player2;
    player2[0x57] = Direction::Up;
    player2[0x53] = Direction::Down;
    player2[0x44] = Direction::Right;
    player2[0x41] = Direction::Left;
    em_.Add(std::unique_ptr<CEntity>(new CSnake(grid_h / 2, 2 * grid_w / 3, 1, player2)));
    Trail::Run(em_, *this);

    std::pair<int, int> food_xy = grid_.SpawnFood();
    em_.Add(std::unique_ptr<CEntity>(new CFood(food_xy.first, food_xy.second)));

    game_over_ = false;
}

void CSnakeGame::HandleInput(WPARAM wParam, LPARAM lParam) {
    keys_pressed_.push_back(wParam);
}

const std::vector<WPARAM>& CSnakeGame::GetKeys() {
    return keys_pressed_;
}

void CSnakeGame::Update() {
    if (game_over_) {
        return;
    }
    Input::Run(em_, *this);
    keys_pressed_.clear();
    Decay::Run(em_, *this);
    for (auto it = em_.begin(); it != em_.end(); it++) {
        (*it)->Update();
    }
    Collision::Run(em_, *this);
    if (game_over_) {
        return;
    }
    Trail::Run(em_, *this);
}

void CSnakeGame::Draw(HDC hdc) {
    grid_.Draw(hdc);
}

CGrid& CSnakeGame::GetGrid() {
    return grid_;
}

void CSnakeGame::GameOver() {
    game_over_ = true;
}