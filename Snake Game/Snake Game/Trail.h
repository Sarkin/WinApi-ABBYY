#pragma once

#include "System.h"

class CTrail : public CSystem {
public:
    CTrail();
    virtual ~CTrail();

    void Run(EntityManager& em);
};

