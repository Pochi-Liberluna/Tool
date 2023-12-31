#pragma once
#ifndef MERSENNE_HPP
#define MERSENNE_HPP

#include <cstdint>
#include <vector>

class Mersenne {
public:
    Mersenne(int exponent);
    uint64_t GetMersenneNumber() const;
    bool CalculateMersennePrime();
    uint64_t GetMersennePrime() const;

private:
    int exponent;
    uint64_t mersenne;
    uint64_t mersennePrime;

    //メルセンヌ数の計算
    void CalculateMersenne();
};

#endif
