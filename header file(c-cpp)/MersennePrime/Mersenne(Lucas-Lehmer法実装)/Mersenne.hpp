//一応ヘッダーファイル内にメルセンヌ数を検証するアルゴリズムであるLucas-Lehmer法の処理を実装してみていますが動作するか分かりません。
//Lucas-Lehmer法を実装していないヘッダーファイルを使った方が使用できる確率は高いと思います。
//アルゴリズムを実装していないヘッダーファイルは https://github.com/Pochi-Liberluna/Tool/tree/main/header file(c-cpp)/MersennePrime/Mersenne(Lucas-Lehmer法未実装)/Mersenne.hpp にあります。
//もし不具合などを見つけてくださったらPRをお願いします。

#pragma once
#ifndef MERSENNE_HPP
#define MERSENNE_HPP

#include <cstdint>

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

    //Lucas-Lehmer法によるメルセンヌ素数の検証
    bool LucasLehmerTest() const;
};

#endif
