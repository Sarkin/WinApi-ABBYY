#pragma once

#include <string>
#include <vector>
#include <map>
#include <typeinfo>

#include "Component.h"

class CEntity {
public:
    CEntity();
    ~CEntity();

    template<class T>
    bool HasComponent() const;

    template<class T>
    T* GetComponent();

    void Attach(CComponent* component);

    void Initialize();
    virtual void Update();

private:
    bool is_initialized_;
    std::map<int, CComponent*> components_;
};