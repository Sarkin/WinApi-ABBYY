#include "Body.h"

#include "Head.h"
#include "Timer.h"

CBody::CBody(int x, int y, int timer) {
    Attach(new CMotion(x, y, Direction::Hold));
    Attach(new CTimer(timer));
}