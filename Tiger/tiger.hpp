//
// Created by den_p on 2/7/2024.
//

#ifndef LAB04_TIGER_HPP
#define LAB04_TIGER_HPP

#include <iostream>
#include <cstdint>
#include <cstring>


class tiger {
public:
    tiger(const char* str, uint64_t length);
    uint64_t* getRes();
private:
    void save_abc();
    void round(uint64_t& a, uint64_t& b, uint64_t& c, uint64_t x, uint64_t mul);
    void pass(uint64_t& a, uint64_t& b, uint64_t& c, int mul);
    void keySchedule();
    void feedForward();
    void compress();
    void tiger_compress(uint64_t *str, uint64_t state[3]);
private:
    uint64_t res[3]{};
    uint64_t state[3]{};
    uint8_t temp[64]{};
    uint64_t x0{}, x1{}, x2{}, x3{}, x4{}, x5{}, x6{}, x7{};
    uint64_t aa{}, bb{}, cc{};
    uint64_t a{}, b{}, c{}, x{}, tmpa{};
    int pass_no{};
    uint64_t i{}, j{};
};


#endif //LAB04_TIGER_HPP
