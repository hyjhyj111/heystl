#pragma once
#include "define.hpp"

NAMESPACE_OPEN
template<typename _Tp>
struct Default_deleter{
    void operator()(_Tp *p) {
        delete p;
    }
};
template<typename _Tp, typename Deleter = Default_deleter<_Tp>>
class unique_ptr{
private:
    _Tp *p;
    using deleter = Deleter;
public:
    explicit unique_ptr(_Tp *ptr) : p(ptr) {}
    ~unique_ptr() {
        if (p)
            deleter(p);
    }
};

NAMESPACE_CLOSE