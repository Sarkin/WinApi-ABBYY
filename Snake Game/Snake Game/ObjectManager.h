#pragma once

#include <vector>

template<typename T>
class CObjectManager {
public:
    CObjectManager();
    ~CObjectManager();

    typename std::vector<T*>::iterator begin() { return objects_.begin(); }
    typename std::vector<T*>::iterator end() { return objects_.end(); }

    void Add(T* object);
    void MarkAdded(T* object);
    void MarkRemoved(T* object);
    void Clear();
    void Update();

private:
    std::vector<T*> objects_;
    std::vector<T*> added_;
    std::vector<T*> removed_;

    void Remove(T* object);
};

