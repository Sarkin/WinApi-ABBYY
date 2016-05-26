#include "PlayerControlled.h"



CPlayerControlled::CPlayerControlled(int player) {
    player_ = player;
}


int CPlayerControlled::GetPlayer() const {
    return player_;
}
