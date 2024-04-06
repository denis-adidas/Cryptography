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

    std::uniform_int_distribution<uint64_t> distrib(7, 1000);
    uint64_t result = distrib(gen);

    while (!isPrime(result)) {
        result = distrib(gen);
    }

    return result;
}

uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

//Extended Euclidean algorithm - need to find d.
uint64_t RSA::gcdExtended(int a, int b, int *x, int *y) {

    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

uint64_t RSA::findMultiplicativeInverse(int a, int m) {
    int k = 1;
    while (true) {
        if ((1 + k * m) % a == 0)
            return (1 + k * m) / a;
        else
            k++;
    }
}

//Need to find coprime with EF
uint64_t RSA::countExp(uint64_t digital) {
    uint32_t e = 2;
    int x, y;
    while (e < digital) {
        if (gcdExtended(e, digital, &x, &y) == 1)
            break;
        else
            e++;
    }
    return e;
}

uint64_t RSA::encrypt() {

//    std::cout << '0' << std::endl;

    uint64_t p = generateRandomNumbers();
    uint64_t q = generateRandomNumbers();

    std::cout << "P: " << p << std::endl;
    std::cout << "q: " << q << std::endl;

    n = p * q;
    eulerFunction = (p - 1) * (q - 1);

    exp = countExp(eulerFunction);

//    std::cout << "EF: " << eulerFunction << std::endl;
//    std::cout << "Exp: " << exp << std::endl;

    d = findMultiplicativeInverse(exp, eulerFunction);

//    std::cout << "d: " << d << std::endl;
//
//    std::cout << "test: " << (d * exp) % eulerFunction  << std::endl;

    pubKey.first = exp;
    pubKey.second = n;

    secretKey.first = d;
    secretKey.second = n;

    k = modPow(m, pubKey.first, pubKey.second);

//    std::cout << "K: " << k << std::endl;

    return k;
}

uint64_t RSA::decrypt() {
    return modPow(k, secretKey.first, secretKey.second);
}



































