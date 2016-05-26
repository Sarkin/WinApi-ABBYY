#pragma once

#include "Entity.h"
#include "SnakeGame.h"

class CSystem {
public:
    CSystem() { }
    virtual ~CSystem() { }

    virtual void Run(EntityManager& em, CSnakeGame gsnake) = 0;
};

