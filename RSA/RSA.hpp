//
// Created by den_p on 3/20/2024.
//

#ifndef RSA_HPP
#define RSA_HPP
#include <cstdint>
#include <tuple>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/random.hpp>


class RSA {
public:
    RSA();
    uint64_t encrypt();
    uint64_t decrypt();
    void signature();
private:
    uint64_t generateRandomNumbers();
    bool isPrime(uint64_t n);
    uint64_t countExp(uint64_t digital);
    uint64_t gcdExtended(int a, int b, int *x, int *y);
    uint64_t findMultiplicativeInverse(int a, int m);
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
