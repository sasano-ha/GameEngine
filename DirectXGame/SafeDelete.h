#pragma once

template <class T>
inline void safedelete(T*& t) {
    delete t;
    t = nullptr;
}