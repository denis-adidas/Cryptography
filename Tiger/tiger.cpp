#include "tiger.hpp"

#define PASSES 3

extern uint64_t table[4*256];

uint64_t* t1 = table;
uint64_t* t2 = table + 256;
uint64_t* t3 = table + 256 * 2 ;
uint64_t* t4 = table + 256 * 3;


void tiger::save_abc() {
    aa = a;
    bb = b;
    cc = c;
}

void tiger::round(uint64_t& a, uint64_t& b, uint64_t& c, uint64_t x, uint64_t mul) {
    c ^= x; \
    a -= t1[static_cast<uint8_t>(c)] ^ \
         t2[static_cast<uint8_t>((static_cast<uint32_t>(c))>>(2*8))] ^ \
     t3[static_cast<uint8_t>((c)>>(4*8))] ^ \
         t4[static_cast<uint8_t>((static_cast<uint32_t>((c)>>(4*8)))>>(2*8))] ; \
    b += t4[static_cast<uint8_t>((static_cast<uint32_t>(c))>>(1*8))] ^ \
         t3[static_cast<uint8_t>((static_cast<uint32_t>(c))>>(3*8))] ^ \
     t2[static_cast<uint8_t>((static_cast<uint32_t>((c)>>(4*8)))>>(1*8))] ^ \
         t1[static_cast<uint8_t>((static_cast<uint32_t>((c)>>(4*8)))>>(3*8))]; \
    b *= mul;
}
void tiger::pass(uint64_t &a, uint64_t &b, uint64_t &c, int mul) {
    round(a,b,c, x0, mul);
      round(b,c,a, x1, mul);
      round(c,a,b, x2, mul);
      round(a,b,c, x3, mul);
      round(b,c,a, x4, mul);
      round(c,a,b, x5 ,mul);
      round(a,b,c, x6, mul);
      round(b,c,a, x7, mul);
}

void tiger::keySchedule() {
    x0 -= x7 ^ 0xA5A5A5A5A5A5A5A5LL;
    x1 ^= x0;
    x2 += x1;
    x3 -= x2 ^ ((~x1)<<19);
    x4 ^= x3;
    x5 += x4;
    x6 -= x5 ^ ((~x4)>>23);
    x7 ^= x6;
    x0 += x7;
    x1 -= x0 ^ ((~x7)<<19);
    x2 ^= x1;
    x3 += x2;
    x4 -= x3 ^ ((~x2)>>23);
    x5 ^= x4;
    x6 += x5;
    x7 -= x6 ^ 0x0123456789ABCDEFLL;
}

void tiger::feedForward() {
    a ^= aa;
    b -= bb;
    c += cc;
}


void tiger::compress() {
    save_abc();
    for(pass_no=0; pass_no<PASSES; pass_no++) { \
        if(pass_no != 0) {
            keySchedule();
        }
        pass(a,b,c,(pass_no==0?5:pass_no==1?7:9)); \
        tmpa=a; a=c; c=b; b=tmpa;} \
    feedForward();
}

void tiger::tiger_compress(uint64_t *str, uint64_t state[3]) {
    a = state[0];
    b = state[1];
    c = state[2];

    x0=str[0]; x1=str[1]; x2=str[2]; x3=str[3];
    x4=str[4]; x5=str[5]; x6=str[6]; x7=str[7];

    compress();

    state[0] = a;
    state[1] = b;
    state[2] = c;
}

tiger::tiger(const char* str, uint64_t length) {

    res[0] = 0x0123456789ABCDEFLL;
    res[1] = 0xFEDCBA9876543210LL;
    res[2] = 0xF096A5B4C3B2E187LL;

    constexpr size_t blockSize = 64;

    for (uint64_t i = length; i >= blockSize; i -= blockSize) {
        for (size_t j = 0; j < blockSize; j++) {
            temp[j ^ 7] = static_cast<unsigned char>(str[j]);
        }
        tiger_compress(reinterpret_cast<uint64_t*>(temp), res);
        str += 8;
    }

    for (size_t j = 0; j < i; j++) {
        temp[j ^ 7] = static_cast<unsigned char>(str[j]);
    }

    temp[i ^ 7] = 0x01;
    i++;

    for (; i & 7; i++) {
        temp[i ^ 7] = 0;
    }

    if (i > 56) {
        std::memset(temp + 56, 0, blockSize - 56);
        tiger_compress(reinterpret_cast<uint64_t*>(temp), res);
        i = 0;
    }

    std::memset(temp + i, 0, blockSize - i);
    *reinterpret_cast<uint64_t*>(&temp[56]) = length << 3;
    tiger_compress(reinterpret_cast<uint64_t*>(temp), res);
}

uint64_t* tiger::getRes() {
    return res;
}




