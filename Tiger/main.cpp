#include "tiger.hpp"

void hash() {
    std::string input;

    std::cin >> input;
    tiger t = tiger(input.c_str(), input.length());
    uint64_t* res = t.getRes();
    printf("Hash of \"%s\":\n\t%08X%08X %08X%08X %08X%08X\n", \
     input.c_str(), \
     static_cast<uint32_t>(res[0]>>32), \
static_cast<uint32_t>(res[0]), \
static_cast<uint32_t>(res[1]>>32), \
static_cast<uint32_t>(res[1]), \
static_cast<uint32_t>(res[2]>>32), \
static_cast<uint32_t>(res[2]) );

}


int main() {
    
    hash();

    return 0;
}
