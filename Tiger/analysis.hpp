#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include "tiger.hpp"
#include <iostream>
#include <vector>


void secondPreimages();
void cypherAnalysis();
uint64_t collision(const std::vector<uint64_t>& randomHashes);

std::string generateRandomString(int length);

#endif //ANALYSIS_HPP
