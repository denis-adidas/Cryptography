//
// Created by den_p on 3/20/2024.
//

#ifndef RSA_HPP
#define RSA_HPP
#include <cstdint>
#include <tuple>


class RSA {
public:
    RSA();
    uint64_t encrypt();
    uint64_t decrypt();
    void signature();
private:
    uint64_t generateRandomNumbers();
    bool isPrime(uint64_t n);
    uint64_t countExp();
public:
    static uint64_t findD();
private:
    uint32_t exp;
    uint32_t n;
    uint32_t d;
    uint64_t m;
    uint64_t k;
    uint64_t eulerFunction;
    std::pair<uint32_t, uint32_t> pubKey;
    std::pair<uint32_t, uint32_t> secretKey;
};



#endif //RSA_HPP
