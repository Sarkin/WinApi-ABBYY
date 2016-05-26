#include "Trail.h"

#include "Head.h"
#include "Body.h"
#include "Motion.h"

namespace Trail {
    void Run(EntityManager& em, CSnakeGame& gsnake) {
        CGrid& grid = gsnake.GetGrid();
        for (auto a = em.begin(); a != em.end(); a++) {
            if ((*a)->HasComponent<CHead>() && (*a)->HasComponent<CMotion>()) {
                CHead* head = (*a)->GetComponent<CHead>();
                int length = head->GetLength();
                CMotion* motion = (*a)->GetComponent<CMotion>();
                std::pair<int, int> coords = motion->GetCoords();;
                grid.Add(coords, length);
                em.MarkAdded(std::unique_ptr<CEntity>(new CBody(coords.first, coords.second, length)));
            }
        }
        em.Update();
    }
}