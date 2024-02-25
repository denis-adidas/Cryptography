#include "tiger.hpp"
#include "analysis.hpp"

extern std::vector<std::string> passwords;

void hashs(const std::string& input) {

    auto t = tiger(input.c_str(), input.length());
    std::cout << t.getHashforPrint(input);


}

int main() {

    // hash("");
    // hash("abc");
    // hash("Tiger");
    // hash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-");
    // hash("ABCDEFGHIJKLMNOPQRSTUVWXYZ=abcdefghijklmnopqrstuvwxyz+0123456789");
    // hash("Tiger - A Fast New Hash Function, by Ross Anderson and Eli Biham");
    // hash("Tiger - A Fast New Hash Function, by Ross Anderson and Eli Biham, proceedings of Fast Software Encryption 3, Cambridge.");
    // hash("Tiger - A Fast New Hash Function, by Ross Anderson and Eli Biham, proceedings of Fast Software Encryption 3, Cambridge, 1996.");
    // hash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-");
    secondPreimages();



    return 0;
}
