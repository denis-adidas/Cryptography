#include "tiger.hpp"

void hash(const std::string& input) {

    auto t = tiger(input.c_str(), input.length());
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

    hash("");
    hash("abc");
    hash("Tiger");
    hash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-");
    hash("ABCDEFGHIJKLMNOPQRSTUVWXYZ=abcdefghijklmnopqrstuvwxyz+0123456789");
    hash("Tiger - A Fast New Hash Function, by Ross Anderson and Eli Biham");
    hash("Tiger - A Fast New Hash Function, by Ross Anderson and Eli Biham, proceedings of Fast Software Encryption 3, Cambridge.");
    hash("Tiger - A Fast New Hash Function, by Ross Anderson and Eli Biham, proceedings of Fast Software Encryption 3, Cambridge, 1996.");
    hash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-");

    return 0;
}
