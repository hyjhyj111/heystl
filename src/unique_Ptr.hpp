#pragma once
#include "define.hpp"

NAMESPACE_OPEN
template<typename T>
struct Default_deleter{
    void operator()(T *p) {
        delete p;
    }
};
template<typename T>
struct Default_deleter<T[]>{
    void operator()(T *p) {
        delete[] p;
    }
};
template<typename T, typename Deleter = Default_deleter<T>>
class unique_ptr{
private:
    T* p;
    [[no_unique_address]] Deleter deleter = Deleter();
    template<typename U, typename UDeleter>
    friend struct unique_ptr;
public:
    explicit unique_ptr(T *ptr) : p(ptr) {}
    unique_ptr(unique_ptr&& that)  noexcept : p{that.p}{
        that.p = nullptr;
    }
    unique_ptr& operator=(unique_ptr &&that)  noexcept {
        if (p) deleter(p);
        deleter = that.deleter;
        p = that.p;
        return *this;
    }
    unique_ptr(const unique_ptr& ) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;
    ~unique_ptr() {
            deleter (p);

    }
};

NAMESPACE_CLOSE