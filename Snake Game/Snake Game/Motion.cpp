#include "Motion.h"

CMotion::CMotion(int x, int y, Direction d) {
    x_ = x;
    y_ = y;
    d_ = d;
}

void CMotion::SetDirection(Direction d) {
    if (GetOppositeDir(d) != d_) {
        d_ = d;
    }
}

void CMotion::Update() {
    x_ += DX[d_];
    y_ += DY[d_];
}

std::pair<int, int> CMotion::GetCoords() const {
    return std::make_pair(x_, y_);
}

bool IsInsideGrid(const CMotion& motion, std::pair<int, int> grid_size) {
    return (motion.x_ >= 0 && motion.x_ < grid_size.first && motion.y_ >= 0 && motion.y_ < grid_size.second);
}

Direction GetOppositeDir(Direction d) {
    switch (d) {
    case Direction::Right:
        return Direction::Left;
    case Direction::Left:
        return Direction::Right;
    case Direction::Up:
        return Direction::Down;
    case Direction::Down:
        return Direction::Up;
    default:
        return Direction::Hold;
    }
}

