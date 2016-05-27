#include "Food.h"

#include "Motion.h"

CFood::CFood(int x, int y) {
    Attach(new CMotion(x, y, Direction::Hold));
}