#include "Motion.h"

CMotion::CMotion(int x, int y, Direction d) {
    x_ = x;
    y_ = y;
    d_ = d;
}

void CMotion::SetDirection(Direction d) {
    d_ = d;
}

void CMotion::Update() {
    x_ += DX[d_];
    y_ += DY[d_];
}

std::pair<int, int> CMotion::GetCoords() const {
    return std::make_pair(x_, y_);
}
