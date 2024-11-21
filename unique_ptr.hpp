#pragma once
#ifndef HEYSTL_UNIQUE_PTR_HPP
#define HEYSTL_UNIQUE_PTR_HPP

#endif //HEYSTL_UNIQUE_PTR_HPP

#include "define.hpp"
NAME_SPACE_HEY_BEGIN
template<typename T>
struct deleter{
    void operator()(T *p) {
        delete p;
    }
};
template<typename T, typename Deleter = deleter<T>>
class unique_ptr{
private:
    T *m_p;
    Deleter deleter;
public:
    explicit unique_ptr(T *p) : m_p(p) {}
    unique_ptr(unique_ptr &&that)  noexcept : m_p{that.m_p} {}
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr &operator=(const unique_ptr&) = delete;
    ~unique_ptr() {
        if (m_p)
            deleter(m_p);
    }
};




NAME_SPACE_HEY_END
