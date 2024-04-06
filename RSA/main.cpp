#include <iostream>
#include "RSA.hpp"


int main() {
    RSA rsa;
    mp::cpp_int encrypted = rsa.encrypt();
    std::cout << "Encrypted message: " << encrypted << std::endl;
    std::cout << "Encryption finished." << std::endl;
    mp::cpp_int decrypted = rsa.decrypt(encrypted);
    std::cout << "Decrypted message: " << decrypted << std::endl;
    std::cout << "Decryption finished." << std::endl;
    return 0;
}

