#pragma once

#include "System.h"

class CCollision : public CSystem {
public:
    CCollision();
    ~CCollision();

    void Run(EntityManager& em, CSnakeGame& gsnake);
};