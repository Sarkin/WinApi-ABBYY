#include "Collision.h"

#include "Decay.h"
#include "Head.h"
#include "Timer.h"
#include "Body.h"
#include "Motion.h"

namespace Collision {
    void Run(EntityManager& em, CSnakeGame& gsnake) {
        /*
        for (auto a = em.begin(); a != em.end(); a++) {
            for (auto b = em.begin(); b != em.end(); b++) {
                if (a == b) {
                    continue;
                }
                if ((*a)->HasComponent<CHead>()) {
                    CHead* head = (*a)->GetComponent<CHead>();
                    CMotion motion = head->GetMotion();
    //                if (!IsInsideGrid(motion, gsnake.GetGridSize())) {
     //               }
                }
            }
        }
        */

    }
}