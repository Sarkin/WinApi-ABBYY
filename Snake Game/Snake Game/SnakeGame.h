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
    void HandleInput(WPARAM, LPARAM);
    const std::vector<WPARAM>& GetKeys();
    void Pause();

    void GameOver();

    CGrid& GetGrid();

private:
    std::vector<WPARAM> keys_pressed_;
    bool game_over_;
    int paused_;
    CGrid grid_;
    EntityManager em_;
};