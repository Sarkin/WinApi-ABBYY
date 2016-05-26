#include "Body.h"

CBody::CBody() {
}

CBody::CBody(CMotion motion, int timer) : motion_(motion), timer_(timer) {
}

CBody::~CBody() {
}

void CBody::Update() {
    timer_--;
}