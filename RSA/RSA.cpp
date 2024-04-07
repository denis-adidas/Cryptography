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

bool RSA::isPrime(mp::cpp_int n) {
    return mp::miller_rabin_test(n, 25); // Проверяем число на простоту с помощью теста Миллера-Рабина
}

mp::cpp_int RSA::generateRandomNumbers() {
    mp::cpp_int prime;
    boost_swap_impl::random_device rng;
    boost::random::uniform_int_distribution<mp::cpp_int> distrib(100, 999999999);
    do {
        prime = distrib(rng);
    } while (!isPrime(prime));
    return prime;
}

mp::cpp_int RSA::modInverse(mp::cpp_int a, mp::cpp_int m) {
    mp::cpp_int a_mp = a;
    mp::cpp_int m_mp = m;
    mp::cpp_int x, y;
    mp::cpp_int gcd = extended_gcd(a_mp, m_mp, x, y);

    if (gcd != 1) {
        return 0;
    }

    if (x < 0) {
        x += m_mp;
    }

    return x.convert_to<uint64_t>();
}

mp::cpp_int RSA::extended_gcd(mp::cpp_int a, mp::cpp_int b, mp::cpp_int &x, mp::cpp_int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    mp::cpp_int x1, y1;
    mp::cpp_int gcd = extended_gcd(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

mp::cpp_int RSA::encrypt() {
        mp::cpp_int p = generateRandomNumbers();
        mp::cpp_int q = generateRandomNumbers();

        n = p * q;
        eulerFunction = (p - 1) * (q - 1);

        exp = 7;

        while ((d = modInverse(exp, eulerFunction)) == 0) {
            p = generateRandomNumbers();
            q = generateRandomNumbers();

            n = p * q;
            eulerFunction = (p - 1) * (q - 1);

            d = modInverse(exp, eulerFunction);
        }


        pubKey.first = exp;
        pubKey.second = n;

        secretKey.first = d;
        secretKey.second = n;

        return mp::powm(m, exp, n);
}

mp::cpp_int RSA::encrypt(const mp::cpp_int& num) {
    m = num;
    mp::cpp_int p = generateRandomNumbers();
    mp::cpp_int q = generateRandomNumbers();

    n = p * q;
    eulerFunction = (p - 1) * (q - 1);

    exp = 7;

    while ((d = modInverse(exp, eulerFunction)) == 0) {
        p = generateRandomNumbers();
        q = generateRandomNumbers();

        n = p * q;
        eulerFunction = (p - 1) * (q - 1);

        d = modInverse(exp, eulerFunction);
    }


    pubKey.first = exp;
    pubKey.second = n;

    secretKey.first = d;
    secretKey.second = n;

    return mp::powm(num, exp, n);
}

mp::cpp_int RSA::decrypt(const mp::cpp_int& encrypted) {
    return mp::powm(encrypted, d, n);
}

std::vector<mp::cpp_int> RSA::signature() {
    std::vector<mp::cpp_int> result;

    std::string str = boost::multiprecision::to_string(m);
    const char* const text = str.c_str();
    auto ptr = reinterpret_cast<const uint8_t*>(text);
    auto hash = sha2::sha224(ptr, strlen(text));

    for (auto c : hash) {
        result.emplace_back(encrypt(static_cast<mp::cpp_int>(c)));
    }
    return result;
}


std::vector<mp::cpp_int> RSA::decryptSignature(const std::vector<mp::cpp_int>& signature) {
    std::vector<mp::cpp_int> decryptedSignature;

    for (const auto& signature_part : signature) {
        mp::cpp_int decrypted_part = decrypt(signature_part);
        decryptedSignature.push_back(decrypted_part);
    }


    return decryptedSignature;
}

std::vector<mp::cpp_int> RSA::blindAttack(const mp::cpp_int& encrypted) {
    std::vector<mp::cpp_int> forgedSignatures;

    if (pubKey.first >= 3 && pubKey.first < pubKey.second && encrypted < pubKey.second) {

        mp::cpp_int s = 123;
        mp::cpp_int signature = mp::powm(s, pubKey.first, pubKey.second);
        mp::cpp_int decodedSignature = mp::powm(signature, modInverse(s, pubKey.second), pubKey.second);

        mp::cpp_int message = (decodedSignature * encrypted) % pubKey.second;

        forgedSignatures.push_back(signature);
        forgedSignatures.push_back(message);
    }

    return forgedSignatures;
}