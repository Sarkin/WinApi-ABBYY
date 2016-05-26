#pragma once

#include <vector>
#include <memory>

template<typename T>
class CObjectManager {
public:
    CObjectManager();
    ~CObjectManager();

    typename std::vector<std::unique_ptr<T>>::iterator begin() { return objects_.begin(); }
    typename std::vector<std::unique_ptr<T>>::iterator end() { return objects_.end(); }

    void Add(std::unique_ptr<T>& object);
    void MarkAdded(std::unique_ptr<T>& object);
    void MarkRemoved(std::unique_ptr<T>& object);
    void Clear();
    void Update();

private:
    std::vector<std::unique_ptr<T>> objects_;
    std::vector<std::unique_ptr<T>> added_;
    std::vector<std::unique_ptr<T>> removed_;

    void Remove(std::unique_ptr<T>& object);
};

template<typename T>
CObjectManager<T>::CObjectManager() {
}


template<typename T>
CObjectManager<T>::~CObjectManager() {
}

template<typename T>
void CObjectManager<T>::Add(std::unique_ptr<T>& object) {
    objects_.push_back(std::move(object));
}

template<typename T>
void CObjectManager<T>::MarkAdded(std::unique_ptr<T>& object) {
    added_.push_back(std::move(object));
}

template<typename T>
void CObjectManager<T>::MarkRemoved(std::unique_ptr<T>& object) {
    removed_.push_back(std::move(object));
}

template<typename T>
void CObjectManager<T>::Clear() {
    objects_.clear();
}

template<typename T>
void CObjectManager<T>::Update() {
    while (!added_.empty()) {
        objects_.push_back(std::move(added_.back()));
        added_.pop_back();
    }

    while (!removed_.empty()) {
        Remove(std::move(removed_.back()));
        removed_.pop_back();
    }
}

template<typename T>
void CObjectManager<T>::Remove(std::unique_ptr<T>& object) {
    for (std::vector<std::unique_ptr<T>>::iterator i = objects_.begin();
    i != objects_.end(); i++) {
        if (*i == 0) {
            objects_.erase(i);
            break;
        }
    }
}
