//
// Created by den_p on 3/20/2024.
//

#ifndef RSA_HPP
#define RSA_HPP
#include <cstdint>
#include <tuple>
#include "sha2.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/random.hpp>

namespace mp = boost::multiprecision;

class RSA {
public:
    RSA();
    mp::cpp_int encrypt();
    mp::cpp_int encrypt(const mp::cpp_int& num);
    mp::cpp_int decrypt(const mp::cpp_int& encrypted);
    std::vector<mp::cpp_int> decryptSignature(const std::vector<mp::cpp_int>& signature);
    std::vector<mp::cpp_int> blindAttack(const mp::cpp_int& encrypted);
    std::vector<mp::cpp_int> signature();
private:
    mp::cpp_int generateRandomNumbers();
    bool isPrime(mp::cpp_int  n);
    mp::cpp_int modInverse(mp::cpp_int a, mp::cpp_int m);
    mp::cpp_int extended_gcd(mp::cpp_int a, mp::cpp_int b, mp::cpp_int &x, mp::cpp_int &y);
private:
    mp::cpp_int exp;
    mp::cpp_int n;
    mp::cpp_int d;
    mp::cpp_int m;
    mp::cpp_int k;
    mp::cpp_int eulerFunction;
    std::pair<mp::cpp_int, mp::cpp_int> pubKey;
    std::pair<mp::cpp_int, mp::cpp_int> secretKey;
};

#endif //RSA_HPP
