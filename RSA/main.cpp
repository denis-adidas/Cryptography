#include <iostream>
#include "RSA.hpp"

int main() {
//    auto test = RSA();
//    test.encrypt();
//    std::cout << test.decrypt();
    std::cout << 720 - RSA::findD();
    return 0;
}
