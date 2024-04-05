#include <iostream>
#include "RSA.hpp"

int main() {
    auto test = RSA();
    test.encrypt();
    std::cout << test.decrypt();
    return 0;
}
