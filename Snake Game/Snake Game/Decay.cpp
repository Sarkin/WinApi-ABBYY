#include "Decay.h"

#include "Head.h"
#include "Timer.h"
#include "Body.h"
#include "Motion.h"

namespace Decay {
    void Run(EntityManager& em, CSnakeGame& gsnake) {
        CGrid& grid = gsnake.GetGrid();
        for (auto a = em.begin(); a != em.end(); a++) {
            if ((*a)->HasComponent<CTimer>() && (*a)->HasComponent<CMotion>()) {
                CTimer* timer = (*a)->GetComponent<CTimer>();
                CMotion* motion = (*a)->GetComponent<CMotion>();
                if (timer->GetTimer() == 0) {
                    em.MarkRemoved(*a);
                } else {
                    grid.Add(motion->GetCoords(), -1);
                }
            }
        }
        em.Update();
    }
}
