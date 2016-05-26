#include "Trail.h"

#include "Head.h"
#include "Body.h"
#include "Motion.h"

CTrail::CTrail() {
}


CTrail::~CTrail() {
}

void CTrail::Run(EntityManager& em) {
    for (auto a = em.begin(); a != em.end(); a++) {
        if ((*a)->HasComponent<CHead>()) {
            CHead* head = (*a)->GetComponent<CHead>();
            int length = head->GetLength();
            CMotion motion = head->GetMotion();
            motion.SetDirection(Direction::Hold);
            em.Add(std::unique_ptr<CEntity>(new CBody(motion, length - 1)));
        }
    }
}
