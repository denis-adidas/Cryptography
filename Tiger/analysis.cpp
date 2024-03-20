#include "analysis.hpp"

static const std::vector<std::string> passwords = {"", "abc", "Tiger"};
static std::vector<uint64_t> passwordsHash;
static const std::vector<uint32_t> hashBits = {8, 10, 12, 14, 16};


void cypherAnalysis() {
    static std::vector<uint64_t> secondPreimagesValue;
    static std::vector<uint64_t> collisionValue;
    for (const auto & bits : hashBits) {
        for (const auto & password : passwords) {
            auto t = tiger(password.c_str(), password.length());
            passwordsHash.emplace_back(t.getHash(bits));
        }
        static std::vector<uint64_t> randomHashes;
        uint64_t steps = 0;
        for (int i = 0; i < passwordsHash.size(); ++i) {
            std::string randomString;
            uint64_t h = passwordsHash[i];
            while (true) {
                randomString = generateRandomString(passwords[i].length());
                auto t = tiger(randomString.c_str(), randomString.length());
                uint64_t newHash = t.getHash(bits);
                if (h == newHash) {
                    steps++;
                    randomHashes.emplace_back(newHash);
                    break;
                }
                randomHashes.emplace_back(newHash);
                steps++;
            }
            uint64_t collisionsSteps = collision(randomHashes);
            secondPreimagesValue.emplace_back(steps);
            collisionValue.emplace_back(collisionsSteps);
            std::cout << "For " << i + 1 << "th hash steps: " << steps << std::endl;
            std::cout << "Size of hash: " << bits << std::endl;
        }
        passwordsHash.clear();
        randomHashes.clear();
    }

}
uint64_t collision(const std::vector<uint64_t>& randomHashes) {
    int steps = 0;
    for (int i = 0; i < passwordsHash.size(); ++i) {
        for (int k = 0; k < passwordsHash.size(); ++k) {
            if (randomHashes[i] == randomHashes[k]) {
                steps++;
                std::cout << "Steps for collision: " << steps << std::endl;
                return steps;
            }
            steps++;
        }
    }
    return 1;
}


std::string generateRandomString(int length) {
    std::string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPRQSTUVWXYZ";
    std::string message;
    for (int i = 0; i < length; ++i) {
        message += characters[rand() % characters.length()];
    }
    return message;
}
