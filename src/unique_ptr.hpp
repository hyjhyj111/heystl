#pragma once
#include "define.hpp"
#include <utility>
#include <type_traits>
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
    explicit unique_ptr(T *ptr) noexcept : p(ptr) {}

    explicit unique_ptr(nullptr_t _) noexcept : p(nullptr) {}

    unique_ptr(const unique_ptr& ) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr(unique_ptr&& that)  noexcept {
        p = std::exchange(that.p, nullptr);
        deleter = std::move(that.deleter);
    }

    unique_ptr& operator=(unique_ptr &&that) noexcept {
        if (this != &that) {
            if (p) deleter(p);
            deleter = std::move(that.deleter);
            p = std::exchange(that.p, nullptr);
        }
        return *this;
    }

    template<typename U, typename UDeleter> requires (std::convertible_to<U*, T*>)
    unique_ptr(unique_ptr<U, UDeleter> &&that) noexcept : p(that.p) {that.p = nullptr;}

    ~unique_ptr() noexcept {
        if (p) deleter(p);
    }

    T *operator->() const noexcept {
        return p;
    }

    T *get() const noexcept {
        return p;
    }

    T *release() noexcept {
        auto t = p;
        p = nullptr;
        return t;
    }

    void reset(T* _p = nullptr) noexcept{
        if (p) deleter(p);
        p = _p;
    }

    explicit operator bool() const noexcept{
        return p != nullptr;
    }

    template<class U, class UDeleter>
    void swap(unique_ptr<U, UDeleter> &that) {
        std::swap(p, that.p);
    }

    bool operator<(const unique_ptr &that) {
        return p < that.p;
    }

    bool operator>(const unique_ptr &that) {
        return p > that.p;
    }

    bool operator<=(const unique_ptr &that) {
        return p <= that.p;
    }

    bool operator>=(const unique_ptr &that) {
        return p >= that.p;
    }

    bool operator==(const unique_ptr &that) {
        return p == that.p;
    }

    bool operator!=(const unique_ptr &that) {
        return p != that.p;
    }

    std::add_lvalue_reference_t<T> operator*() const noexcept {
        return *p;
    }

};

template <class T, class Deleter>
struct unique_ptr<T[], Deleter> : public unique_ptr<T, Deleter> {
    using unique_ptr<T, Deleter>::unique_ptr;

    std::add_lvalue_reference_t<T> operator[](std::size_t _i) {
        return this->get()[_i];
    }
};

template<typename T, typename ...Args, std::enable_if<!std::is_unbounded_array_v<T>, int>::type = 0>
unique_ptr<T> make_unique(Args &&...args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T, std::enable_if<!std::is_unbounded_array_v<T>, int>::type = 0>
unique_ptr<T> make_unique_for_overwrite() {
    return unique_ptr<T>(new T);
}

template<typename T, std::enable_if<std::is_unbounded_array_v<T>, int>::type = 0>
unique_ptr<T> make_unique(size_t len) {
    return unique_ptr<T>(new std::remove_extent_t<T>[len]);
}

template<typename T, std::enable_if<std::is_unbounded_array_v<T>, int>::type = 0>
unique_ptr<T> make_unique_for_overwrite(size_t len) {
    return unique_ptr<T>(new std::remove_extent_t<T>[len]);
}
NAMESPACE_CLOSE