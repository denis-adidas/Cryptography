//
// Created by den_p on 3/20/2024.
//

#include "RSA.hpp"
#include <iostream>
#include <cmath>
#include <random>


//ADD INIT D E AND OTHER
RSA::RSA() {

    std::string input;
    std::cout << "Enter the message like a number: " << std::endl;
    std::cin >> m;
//
//    std::cout << "Enter the exponent for encrypt (enter number bigger than 3 for safety): " << std::endl;
//    std::cin >> exp;
//
//    std::string temp;
//    for (char & it : input) {
//        temp.append(std::to_string(static_cast<int>(it)));
//    }
//    m = std::stol(temp);
}

bool RSA::isPrime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

uint64_t RSA::generateRandomNumbers() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<uint64_t> distrib(7, std::numeric_limits<uint64_t>::max());
    uint64_t result = distrib(gen);

    while (!isPrime(result)) {
        result = distrib(gen);
    }

    return result;
}

//Extended Euclidean algorithm - need to find d.
uint64_t RSA::findD() {
    uint64_t q, r, x1 = 0,
             x2 = 1, y1 = 1, y2 = 0;
    uint64_t a = 720;
    uint64_t b = 691;

    uint64_t x, y;
    while (b > 0) {
        q = a / b;
        r = a - q * b;
        x = x2 - q * x1;
        y = y2 - q *y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    return std::min(x2, y2);
}


uint64_t RSA::countExp() {
    for (int i = 1; i < sqrt(eulerFunction); ++i) {
        if (eulerFunction % i == 1)
            return i;
    }
}

uint64_t RSA::encrypt() {

//    std::cout << '0' << std::endl;

    uint64_t p = generateRandomNumbers();
    uint64_t q = generateRandomNumbers();

    std::cout << "P: " << p << std::endl;
    std::cout << "q: " << q << std::endl;

    n = p * q;
    eulerFunction = (p - 1) * (q - 1);

    exp = countExp();

    std::cout << "EF: " << eulerFunction << std::endl;
    std::cout << "Exp: " << exp << std::endl;

    d = eulerFunction - findD();

    std::cout << "d: " << d << std::endl;

    std::cout << "test: " << eulerFunction % (d * exp)  << std::endl;

    pubKey.first = exp;
    pubKey.second = n;

    secretKey.first = d;
    secretKey.second = n;

    k = static_cast<uint64_t>(std::pow(m, pubKey.first)) % pubKey.second;

    std::cout << "K: " << k << std::endl;

    return k;
}

uint64_t RSA::decrypt() {
    m = secretKey.second % static_cast<uint64_t>(std::pow(k, secretKey.first)) ;
    return m;
}



































