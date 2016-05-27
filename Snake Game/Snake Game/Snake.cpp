#include "Snake.h"

#include "Head.h"
#include "PlayerControlled.h"

CSnake::CSnake(int x, int y, int player, std::map<WPARAM, Direction> key_mapping) {
    Attach(new CHead(1));
    Attach(new CMotion(x, y, Direction::Hold));
    Attach(new CPlayerControlled(player, key_mapping));
}