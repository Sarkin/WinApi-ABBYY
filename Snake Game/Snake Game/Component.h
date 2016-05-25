#pragma once

class CEntity;

class CComponent {
public:
    bool IsActive() const { return is_active_; }
    void SetIsActive(bool is_active) { is_active_ = is_active; }
    void SetParent(CEntity* entity) { entity_ = entity; }

    CComponent() : is_active_(true) { }
    virtual ~CComponent() { }

    virtual void Cleanup() { }
    virtual void Update() { }
    virtual void Initialize() { }

protected:
    bool is_active_;
    CEntity* entity_;
};