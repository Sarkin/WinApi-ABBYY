#include "Motion.h"



CMotion::CMotion() {
}


CMotion::~CMotion() {
}

void CMotion::Update() {
    x_ += DX[d_];
    y_ += DY[d_];
}
