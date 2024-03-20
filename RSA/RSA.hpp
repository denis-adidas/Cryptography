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
    std::pair<uint32_t, uint32_t> encrypt();
    std::pair<uint32_t, uint32_t> decrypt();
    void signature();
private:
    std::pair<uint32_t, uint32_t> generateRandomNumbers();
    uint64_t eulerFunction();
    bool isPrime();
private:
    uint32_t exp;
    uint32_t n;
    uint32_t d;
    uint64_t m;
    std::pair<uint32_t, uint32_t> pubKey;
    std::pair<uint32_t, uint32_t> secretKey;
};



#endif //RSA_HPP
