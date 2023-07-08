//Cで書いたものをGPTを使ってC++に変換しました。
#include <cstdio>
#include <random>
using bint = unsigned long long;

class crypto {
private:
    bint p, q, n, l, e, d;
    bint M, MAX;
public:
    void init();
    crypto() {
        MAX = 8000000;
        init();
    }
    bint extended_euclidean(bint&, bint&);
    bint gcd(bint, bint);
    bint lcm(bint, bint);
    bint modPow(bint, bint, bint);
    bint modinv(const bint&, const bint&);
    bint Chinese_Remainder_Theorem(bint&, bint&, bint&, bint&);
    void start();
};

bint crypto::extended_euclidean(bint& a, bint& b) {
    bint x = 1, y = 0, u = 0, v = 1, s = a, t = b;
    bint k = 0, tmp = 0;
    while (t) {
        k = s / t;
        s -= k * t;
        tmp = s;
        s = t;
        t = tmp;
        x -= k * u;
        tmp = x;
        x = u;
        u = tmp;
        y -= k * v;
        tmp = y;
        y = v;
        v = tmp;
    }
    if (x > y) return y;
    return x;
}

bint crypto::gcd(bint x, bint y) {
    while (1) {
        if (y == 0) return x;
        x = x % y;
        if (x == 0) return y;
        y = y % x;
    }
}

bint crypto::lcm(bint a, bint b) {
    return a * b / gcd(a, b);
}

bint crypto::modPow(bint a, bint k, bint n) {
    a %= n;

    if (a == 0 || n == 0) return 0;
    if (k == 0) return 1 % n;

    bint i;
    bint value = 1;
    for(i = 0; i < k; i++) {
        value *= a;
        if(value >= n) {
            value %= n;
        }
    }
    return value;
}

bint crypto::modinv(const bint &a, const bint &m) {
    bint j = 1, i = 0, b = m, c = a, x, y;
    while (c != 0) {
        x = b / c;
        y = b - x*c;
        b = c;
        c = y;
        y = j;
        j = i - j*x;
        i = y;
    }
    if (i < 0) i += m;
    return i;
}

bint crypto::Chinese_Remainder_Theorem(bint &p, bint &q, bint &c, bint &d) {
    bint m1, m2, dp, dq, qinv, m, h;
    qinv = modinv(q, p);

    dp = d % (p-1);
    dq = d % (q-1);

    m1 = modPow(c, dp, p);
    m2 = modPow(c, dq, q);

    h = qinv * (m1 - m2);
    m = m2 + h * q;
    return m;
}

void crypto::init() {
    bint* sieve = new bint[MAX];
    for (size_t i = 0; i < MAX; i++) sieve[i] = true;
    bint tmp;
    sieve[1] = false;
    for(size_t i = 3; i <= MAX; i+=2) {
        if(sieve[i] == true) {
            for(size_t j = 2 * i; j <= MAX; j += i) {
                sieve[j] = false;
            }
        }
    }
    std::random_device rnd;
    std::mt19937_64 mt(rnd());
    std::uniform_int_distribution<> rand(300000, MAX);
    tmp = rand(mt);
    while (1) {
        if (sieve[tmp]) {
            p = tmp;
            break;
        }
        tmp += 1;
    }
    tmp = rand(mt);
    while (1) {
        if (sieve[tmp]) {
            q = tmp;
            break;
        }
        tmp += 1;
    }
    if (p < q) {
        tmp = p;
        p = q;
        q = tmp;
    }
    delete [] sieve;
}

void crypto::start() {
    while (1) {
        n = p * q;

        l = lcm(p-1, q-1);

        e = 65535;
        while (gcd(l, e) != 1) {
            e++;
        }

        d = extended_euclidean(l, e);
        if (((e * d) % l) == 1) break;
        init();
    }
    printf("P : %lld   Q : %lld\n", p, q);

    printf("N : %lld   L : %lld   E : %lld   D : %lld\n", n, l, e, d);

    bint plain_num;
    printf("plain_num : ");
    scanf("%llu", &plain_num);

    //暗号化
    bint encrypted_num = modPow(plain_num, e, n);
    printf("encrypted_num: %llu\n", encrypted_num);

    //復号化
    M = Chinese_Remainder_Theorem(p, q, encrypted_num, d);
    printf("decrypted_num(CRT): %llu\n", M);
    bint decrypted_num = modPow(encrypted_num, d, n);
    printf("decrypted_num:      %llu\n", decrypted_num);
}

int main() {
    crypto* t;
    t = new crypto();
    t->start();
    delete t;
    return 0;
}
