#include "Entity.h"

CEntity::CEntity() : is_initialized_(false) {
}


CEntity::~CEntity() {
    for (auto it = components_.begin(); it != components_.end(); it++) {
        it->second->Cleanup();
        delete &it;
    }
}

template<class T>
bool CEntity::HasComponent() const {
    int key = typeid(T).hash_code();
    bool has_component = components_.find(key) != components_.end();

    return has_component;
}

template<class T>
T* CEntity::GetComponent() {
    T* component = 0;

    if (HasComponetn<T>()) {
        int key = typeid(T).hash_code();
        component = static_cast<T*>(components_.find(key)->second);
    }
    else {
        std::string message = ": get failed.  componet of type " + typeid(T).name() +
            " could not be found.";
        throw std::invalid_argument(message);
    }

    return component;
}

void CEntity::Attach(CComponent* component) {
    int key = typeid(*component).hash_code();

    if (components_.find(key) == components_.end()) {
        components_.insert(std::make_pair(key, component));
        component->SetParent(this);

        if (is_initialized_) {
            component->Initialize();
        }
    } else {
        std::string message = std::string(typeid(CEntity).name()) +
            ": Attach failed.  component of type " + typeid(*component).name() +
            " could not be added because a component of the same type already exists.";
        throw std::invalid_argument(message);
    }
}

void CEntity::Initialize() {
    is_initialized_ = true;

    for (auto it = components_.begin(); it != components_.end(); it++) {
        it->second->Initialize();
    }
}

void CEntity::Update() {
    for (auto it = components_.begin(); it != components_.end(); it++) {
        if (it->second->IsActive()) {
            it->second->Update();
        }
    }
}
