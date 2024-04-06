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
        std::cerr << "Error: No inverse exists for given arguments." << std::endl;
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

mp::cpp_int RSA::decrypt(mp::cpp_int encrypted) {
    return mp::powm(encrypted, d, n);
}



































