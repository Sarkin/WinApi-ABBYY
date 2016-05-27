#include "Input.h"

#include "PlayerControlled.h"

namespace Input {
    void Run(EntityManager& em, CSnakeGame& gsnake) {
        const std::vector<WPARAM>& keys_pressed = gsnake.GetKeys();
        for (auto a = em.begin(); a != em.end(); a++) {
            if ((*a)->HasComponent<CPlayerControlled>()) {
                CPlayerControlled* player_controller = (*a)->GetComponent<CPlayerControlled>();
                for (auto key : keys_pressed) {
                    if (player_controller->HandleInput(key)) {
                        break;
                    }
                }
            }
        }
    }
}