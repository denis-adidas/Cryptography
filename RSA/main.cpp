#include <iostream>
#include "RSA.hpp"




int main() {
    auto test = RSA();
    test.encrypt();
    std::cout << "Res: " << test.decrypt();
//    std::cout << findMultiplicativeInverse(691, 720);
    return 0;
}
