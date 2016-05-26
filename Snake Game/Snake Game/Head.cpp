#include "Head.h"

CHead::CHead() {
}


CHead::~CHead() {
}

void CHead::Update() {
    motion_.Update();
}

CMotion CHead::GetMotion() const {
    return motion_;
}

int CHead::GetLength() const {
    return length_;
}
