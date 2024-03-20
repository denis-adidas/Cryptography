//
// Created by den_p on 3/20/2024.
//

#include "RSA.hpp"
#include <iostream>

RSA::RSA() {
    std::string input;
    std::cout << "Enter the message: " << std::endl;
    std::cin >> input;

    std::cout << "Enter the exponent for encrypt (enter number bigger "
                 "than 3 for safety): " << std::endl;
    std::cin >> exp;

    std::string temp;
    for (char & it : input) {
        temp.append(std::to_string(static_cast<int>(it)));
    }
    std::cout << temp << std::endl;
    m = strtol(input.c_str(), nullptr, 10);
    std::cout << m;
}
