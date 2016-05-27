#include "SnakeGame.h"

#include "Trail.h"
#include "Decay.h"
#include "Collision.h"
#include "Food.h"
#include "PlayerControlled.h"
#include "Input.h"

CSnakeGame::CSnakeGame(int grid_h, int grid_w) : grid_(grid_h, grid_w, 10) {
    std::pair<int, int> xy1(grid_h / 2, 2 * grid_w / 3); // = grid_.GetFreeCell();
    std::map<WPARAM, Direction> player1;
    player1[VK_UP] = Direction::Up;
    player1[VK_DOWN] = Direction::Down;
    player1[VK_RIGHT] = Direction::Right;
    player1[VK_LEFT] = Direction::Left;
    em_.Add(std::unique_ptr<CEntity>(new CSnake(xy1.first, xy1.second, 0, player1)));
    std::pair<int, int> xy2(grid_h / 2, grid_w / 3);
    /*
    do {
        xy2 = grid_.GetFreeCell();
    } while (xy2 == xy1);
    */
    std::map<WPARAM, Direction> player2;
    player2[0x57] = Direction::Up;
    player2[0x53] = Direction::Down;
    player2[0x44] = Direction::Right;
    player2[0x41] = Direction::Left;
    em_.Add(std::unique_ptr<CEntity>(new CSnake(xy2.first, xy2.second, 1, player2)));
    Trail::Run(em_, *this);

    std::pair<int, int> food_xy = grid_.SpawnFood();
    em_.Add(std::unique_ptr<CEntity>(new CFood(food_xy.first, food_xy.second)));

    game_over_ = false;
    paused_ = 0;
}

void CSnakeGame::HandleInput(WPARAM wParam, LPARAM lParam) {
    keys_pressed_.push_back(wParam);
}

const std::vector<WPARAM>& CSnakeGame::GetKeys() {
    return keys_pressed_;
}

void CSnakeGame::Pause() {
    paused_ = 1 - paused_;
}

void CSnakeGame::Update() {
    if (paused_ || game_over_) {
        return;
    }
    Input::Run(em_, *this);
    keys_pressed_.clear();
    Decay::Run(em_, *this);
    for (auto it = em_.begin(); it != em_.end(); it++) {
        (*it)->Update();
    }
    Collision::Run(em_, *this);
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