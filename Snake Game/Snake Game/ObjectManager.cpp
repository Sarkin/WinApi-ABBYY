#include "ObjectManager.h"


template<typename T>
CObjectManager<T>::CObjectManager() {
}


template<typename T>
CObjectManager<T>::~CObjectManager() {
}

template<typename T>
void CObjectManager<T>::Add(T* object) {
    objects_.push_back(object);
}

template<typename T>
void CObjectManager<T>::MarkAdded(T* object) {
    added_.push_back(object);
}

template<typename T>
void CObjectManager<T>::MarkRemoved(T* object) {
    removed_.push_back(object);
}

template<typename T>
void CObjectManager<T>::Clear() {
    objects_.clear();
}

template<typename T>
void CObjectManager<T>::Update() {
    while (!added_.empty()) {
        objects_.push_back(added_.back());
        added_.pop_back();
    }

    while (!removed_.empty()) {
        Remove(removed_.back());
        removed_.pop_back();
    }
}

template<typename T>
void CObjectManager<T>::Remove(T* object) {
    for (boost::ptr_vector<T>::iterator i = objects_.begin();
    i != objects_.end(); i++) {
        if (&*i == object) {
            objects_.erase(i);
            break;
        }
    }
}
