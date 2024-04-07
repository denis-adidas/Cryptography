#include <iostream>
#include "RSA.hpp"
#include "sha2.h"


int main() {
//    RSA rsa;
//    mp::cpp_int encrypted = rsa.encrypt();
//    std::cout << "Encrypted message: " << encrypted << std::endl;
//    std::cout << "Encryption finished." << std::endl;
//    mp::cpp_int decrypted = rsa.decrypt(encrypted);
//    std::cout << "Decrypted message: " << decrypted << std::endl;
//    std::cout << "Decryption finished." << std::endl;


    //    const char* const text = "abc";
    //    auto ptr = reinterpret_cast<const uint8_t*>(text);
    //    auto hash = sha2::sha224(ptr, strlen(text));

    RSA rsa;

    auto hash = rsa.signature();

    std::cout << hash.size() << std::endl;

    for (const auto& c : hash) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    
    mp::cpp_int encrypted = rsa.encrypt();
    for( auto c : rsa.blindAttack(encrypted)) {
        std::cout << c << ' ';
    }

    return 0;
}

