#pragma once

#include "Component.h"

#include <algorithm>

const int DX[5] = { 1, 0, -1, 0, 0 };
const int DY[5] = { 0, 1, 0, -1, 0 };

enum Direction {
    Right, Up, Left, Down, Hold
};

class CMotion : public CComponent {
public:
    CMotion(int x, int y, Direction d);

    void SetDirection(Direction d);
    std::pair<int, int> GetCoords() const;
    void Update();

 //   friend bool IsInsideGrid(const CMotion&, std::pair<int, int>);

private:
    int x_;
    int y_;
    Direction d_;
};
/*
bool IsInsideGrid(const CMotion& motion, std::pair<int, int> grid_size) {
    return (motion.x_ >= 0 && motion.x_ < grid_size.first && motion.y_ >= 0 && motion.y_ < grid_size.second);
}
*/
