#include "RC6.hpp"
#include "Util.hpp"



int main() {

    std::vector<uint32_t> key = generateRandomKey();
    std::vector<uint32_t> iv = generateRandomIV();
    RC6 rc6(key);

    std::string inputText;

    encryptBMPFile(rc6,"../data/image.bmp");
//    encryptTXTFile(rc6, "../data/input.txt");



    return 0;
}
