#include "PlayerControlled.h"

#include "Entity.h"

CPlayerControlled::CPlayerControlled(int player, std::map<WPARAM, Direction> key_mapping) : player_(player), key_mapping_(key_mapping) {
}


int CPlayerControlled::GetPlayer() const {
    return player_;
}

bool CPlayerControlled::HandleInput(WPARAM wParam) {
    if (key_mapping_.find(wParam) == key_mapping_.end()) {
        return false;
    }
    CMotion* motion = entity_->GetComponent<CMotion>();
    Direction d = key_mapping_[wParam];
    motion->SetDirection(d);
    return true;
}
