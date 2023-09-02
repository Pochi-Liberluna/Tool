#include "Mersenne.hpp"
#include <iostream>

int main(){
    int exponent = 7; //例:指数部を設定

    Mersenne mersenne(exponent);

    //メルセンヌ数を計算して表示
    std::cout << "Mersenne Number (2^" << exponent << " - 1): " << mersenne.GetMersenneNumber() << std::endl;

    //メルセンヌ素数を計算して表示
    if(mersenne.CalculateMersennePrime()){
        std::cout << "Mersenne Prime (2^" << exponent << " - 1): " << mersenne.GetMersennePrime() << std::endl;
    } else{
        std::cout << "No Mersenne Prime found for 2^" << exponent << " - 1." << std::endl;
    }

    return 0;
}
