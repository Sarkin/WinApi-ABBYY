#pragma once

#include "Entity.h"
#include "ObjectManager.h"

typedef CObjectManager<CEntity> EntityManager;

class CSystem {
public:
    CSystem();
    ~CSystem();

    virtual void Run(EntityManager& em) = 0;
};

