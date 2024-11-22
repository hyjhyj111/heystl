#include "unique_Ptr.hpp"
#include <iostream>
#include <memory>
using namespace hey;
int main() {
    unique_ptr<int> q(new int);
    q = unique_ptr<int> (new int);
    return 0;
}