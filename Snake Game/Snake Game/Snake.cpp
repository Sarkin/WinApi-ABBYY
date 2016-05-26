#include "Snake.h"

#include "Head.h"
#include "PlayerControlled.h"

CSnake::CSnake(int x, int y, int player) {
    Attach(new CHead(5));
    Attach(new CMotion(x, y, Direction::Up));
    Attach(new CPlayerControlled(player));
}