#include "Collision.h"

#include "Decay.h"
#include "Head.h"
#include "Timer.h"
#include "Body.h"
#include "Motion.h"
#include "Food.h"

namespace Collision {
    void Run(EntityManager& em, CSnakeGame& gsnake) {
        CGrid& grid = gsnake.GetGrid();
        for (auto a = em.begin(); a != em.end(); a++) {
            if (!(*a)->HasComponent<CMotion>() || !(*a)->HasComponent<CHead>()) {
                continue;
            }
            if (!IsInsideGrid(*(*a)->GetComponent<CMotion>(), gsnake.GetGrid().GetGridSize())) {
                gsnake.GameOver();
            }
        }
        for (auto a = em.begin(); a != em.end(); a++) {
            if ((*a).get() == 0 || !(*a)->HasComponent<CMotion>() || !(*a)->HasComponent<CHead>()) {
                continue;
            }
            CHead* head_a = (*a)->GetComponent<CHead>();
            CMotion* motion_a = (*a)->GetComponent<CMotion>();
            for (auto b = em.begin(); b != em.end(); b++) {
                if ((*b).get() == 0 || a == b || !(*b)->HasComponent<CMotion>()) {
                    continue;
                }
                CMotion* motion_b = (*b)->GetComponent<CMotion>();
                if (motion_a->GetCoords() == motion_b->GetCoords()) {
                    std::pair<int, int> xy = motion_b->GetCoords();
                    if (grid.Get(xy.first, xy.second) < 0) {
                        head_a->SetLength(head_a->GetLength() + 1);
                        xy = grid.EatFood(xy.first, xy.second);
                        em.MarkAdded(std::unique_ptr<CEntity>(new CFood(xy.first, xy.second)));
                        em.MarkRemoved(*b);
                    }
                }
            }
        }
        em.Update();
    }
}