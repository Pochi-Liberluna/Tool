#include"Mersenne.hpp"
#include<gmpxx.h>
#include<cmath>

Mersenne::Mersenne(int exponent) : exponent(exponent){
    CalculateMersenne();
}

void Mersenne::CalculateMersenne(){
    mpz_class two(2);
    mpz_class power;
    mpz_ui_pow_ui(power.get_mpz_t(), two.get_mpz_t(), exponent);
    mersenne = power - 1;
}

uint64_t Mersenne::GetMersenneNumber() const{
    return mpz_get_ui(mersenne.get_mpz_t());
}

bool Mersenne::CalculateMersennePrime(){
    mpz_class m_prime;
    mpz_class m_minus_one;

    mpz_sub_ui(m_minus_one.get_mpz_t(), mersenne.get_mpz_t(), 1);

    if(mpz_probab_prime_p(m_minus_one.get_mpz_t(), 25)){
        mersennePrime = mersenne.get_ui();
        return true;
    }

    return false;
}

uint64_t Mersenne::GetMersennePrime() const{
    return mersennePrime;
}
