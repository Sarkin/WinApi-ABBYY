#include "Collision.h"

#include "Head.h"

CCollision::CCollision() {
}


CCollision::~CCollision() {
}

void CCollision::Run(EntityManager& em) {
    for (auto a = em.begin(); a != em.end(); a++) {
        for (auto b = em.begin(); b != em.end(); b++) {
            if (a == b) {
                continue;
            }
            if ((*a)->HasComponent<CHead>()) {

            }
        }
    }
}
