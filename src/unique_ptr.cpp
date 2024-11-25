#include <cstdio>
#include <vector>
#include "unique_ptr.hpp"
using namespace hey;
struct MyClass {
    int a, b, c;
};

struct Animal {
    virtual void speak() = 0;
    virtual ~Animal() = default;
};

struct Dog : Animal {
    int age;

    Dog(int age_) : age(age_) {
    }

    virtual void speak() {
        printf("Bark! I'm %d Year Old!\n", age);
    }
};

struct Cat : Animal {
    int &age;

    Cat(int &age_) : age(age_) {
    }

    virtual void speak() {
        printf("Meow! I'm %d Year Old!\n", age);
    }
};
class t{
public:
    void operator() (Cat *p) { delete p;}
};
int main() {
    std::vector<unique_ptr<Animal>> zoo;
    int age = 3;
    zoo.push_back(make_unique<Cat>(age));
    zoo.push_back(make_unique<Dog>(age));
    zoo.push_back(make_unique<Cat>(age));
    for (auto const &a: zoo) {
        a->speak();
    }
    age++;
    for (auto const &a: zoo) {
        a->speak();
    }
    auto x = make_unique<int[]>(10);
    std::printf("%d \n", x[2]);
    unique_ptr<Cat, t> qqq;
    t{}(new Cat(age));
    return 0;
}