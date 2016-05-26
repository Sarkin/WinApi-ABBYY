#pragma once

#include <string>
#include <vector>
#include <map>
#include <typeinfo>

#include "Component.h"
#include "ObjectManager.h"

typedef CObjectManager<CEntity> EntityManager;

class CEntity {
public:
    CEntity();
    ~CEntity();

    template<class T>
    inline bool HasComponent() const;

    template<class T>
    T* GetComponent();

    void Attach(CComponent* component);

    void Initialize();
    virtual void Update();

private:
    bool is_initialized_;
    std::map<int, CComponent*> components_;
};

template<class T>
bool CEntity::HasComponent() const {
    int key = typeid(T).hash_code();
    bool has_component = components_.find(key) != components_.end();

    return has_component;
}

template<class T>
T* CEntity::GetComponent() {
    T* component = 0;

    if (HasComponent<T>()) {
        int key = typeid(T).hash_code();
        component = static_cast<T*>(components_.find(key)->second);
    }
    else {
        std::string message = std::string(": get failed.  componet of type ") + std::string(typeid(T).name()) +
            std::string(" could not be found.");
        throw std::invalid_argument(message);
    }

    return component;
}

