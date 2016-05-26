#include "Motion.h"

CMotion::CMotion() {
}


CMotion::~CMotion() {
}

void CMotion::SetDirection(Direction d) {
    d_ = d;
}

void CMotion::Update() {
    x_ += DX[d_];
    y_ += DY[d_];
}
