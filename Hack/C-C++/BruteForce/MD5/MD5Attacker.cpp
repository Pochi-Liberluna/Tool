#include <iostream>
#include <cstring>
#include <cstdlib>

#define MAX_BUFFER_SIZE 1024
#define BYTE unsigned char
#define WORD unsigned long int
#define GET_WORD(n,b,i)               \
{                                    \
    (n) = ((WORD)(b)[(i)])          \
        | ((WORD)(b)[(i) + 1] << 8)  \
        | ((WORD)(b)[(i) + 2] << 16) \
        | ((WORD)(b)[(i) + 3] << 24); \
}
#define PUT_WORD(n,b,i)               \
{                                    \
    (b)[(i)]     = (BYTE)((n));       \
    (b)[(i) + 1] = (BYTE)((n) >> 8);  \
    (b)[(i) + 2] = (BYTE)((n) >> 16); \
    (b)[(i) + 3] = (BYTE)((n) >> 24); \
}

typedef struct {
    WORD total[2];
    WORD state[4];
    BYTE buffer[64];
} md5_context;

void MD5_starts(md5_context *ctx) {
    ctx->total[0] = 0;
    ctx->total[1] = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
}

void MD5_process(md5_context *ctx, BYTE data[64]) {
    WORD X[16], A, B, C, D;

    GET_WORD(X[0],  data,  0);
    GET_WORD(X[1],  data,  4);
    GET_WORD(X[2],  data,  8);
    GET_WORD(X[3],  data, 12);
    GET_WORD(X[4],  data, 16);
    GET_WORD(X[5],  data, 20);
    GET_WORD(X[6],  data, 24);
    GET_WORD(X[7],  data, 28);
    GET_WORD(X[8],  data, 32);
    GET_WORD(X[9],  data, 36);
    GET_WORD(X[10], data, 40);
    GET_WORD(X[11], data, 44);
    GET_WORD(X[12], data, 48);
    GET_WORD(X[13], data, 52);
    GET_WORD(X[14], data, 56);
    GET_WORD(X[15], data, 60);

#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32 - n)))

#define FF(a,b,c,d,k,s,t)                                \
{                                                       \
    a += ((b & c) | (~b & d)) + X[k] + t; a = ROTATE_LEFT(a,s) + b; \
}

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];

    FF(A, B, C, D,  0,  7, 0xD76AA478);
    FF(D, A, B, C,  1, 12, 0xE8C7B756);
    FF(C, D, A, B,  2, 17, 0x242070DB);
    FF(B, C, D, A,  3, 22, 0xC1BDCEEE);
    FF(A, B, C, D,  4,  7, 0xF57C0FAF);
    FF(D, A, B, C,  5, 12, 0x4787C62A);
    FF(C, D, A, B,  6, 17, 0xA8304613);
    FF(B, C, D, A,  7, 22, 0xFD469501);
    FF(A, B, C, D,  8,  7, 0x698098D8);
    FF(D, A, B, C,  9, 12, 0x8B44F7AF);
    FF(C, D, A, B, 10, 17, 0xFFFF5BB1);
    FF(B, C, D, A, 11, 22, 0x895CD7BE);
    FF(A, B, C, D, 12,  7, 0x6B901122);
    FF(D, A, B, C, 13, 12, 0xFD987193);
    FF(C, D, A, B, 14, 17, 0xA679438E);
    FF(B, C, D, A, 15, 22, 0x49B40821);

#undef FF

#define GG(a,b,c,d,k,s,t)                                \
{                                                       \
    a += ((b & d) | (c & ~d)) + X[k] + t; a = ROTATE_LEFT(a,s) + b; \
}

#define HH(a,b,c,d,k,s,t)                                \
{                                                       \
    a += (b ^ c ^ d) + X[k] + t; a = ROTATE_LEFT(a,s) + b; \
}

#define II(a,b,c,d,k,s,t)                                \
{                                                       \
    a += (c ^ (b | ~d)) + X[k] + t; a = ROTATE_LEFT(a,s) + b; \
}

    GG(A, B, C, D,  1,  5, 0xF61E2562);
    GG(D, A, B, C,  6,  9, 0xC040B340);
    GG(C, D, A, B, 11, 14, 0x265E5A51);
    GG(B, C, D, A, 14, 20, 0xF6BB4B60);
    GG(A, B, C, D,  5,  5, 0xD62F105D);
    GG(D, A, B, C, 10,  9, 0x02441453);
    GG(C, D, A, B, 15, 14, 0xD8A1E681);
    GG(B, C, D, A,  4, 20, 0xE7D3FBC8);
    GG(A, B, C, D,  9,  5, 0x21E1CDE6);
    GG(D, A, B, C, 14,  9, 0xC33707D6);
    GG(C, D, A, B,  3, 14, 0xF4D50D87);
    GG(B, C, D, A,  8, 20, 0x455A14ED);
    GG(A, B, C, D, 13,  5, 0xA9E3E905);
    GG(D, A, B, C,  2,  9, 0xFCEFA3F8);
    GG(C, D, A, B,  7, 14, 0x676F02D9);
    GG(B, C, D, A, 12, 20, 0x8D2A4C8A);

    HH(A, B, C, D,  5,  4, 0xFFFA3942);
    HH(D, A, B, C,  8, 11, 0x8771F681);
    HH(C, D, A, B, 11, 16, 0x6D9D6122);
    HH(B, C, D, A, 14, 23, 0xFDE5380C);
    HH(A, B, C, D,  1,  4, 0xA4BEEA44);
    HH(D, A, B, C,  4, 11, 0x4BDECFA9);
    HH(C, D, A, B,  7, 16, 0xF6BB4B60);
    HH(B, C, D, A, 10, 23, 0xBEBFBC70);
    HH(A, B, C, D, 13,  4, 0x289B7EC6);
    HH(D, A, B, C,  0, 11, 0xEAA127FA);
    HH(C, D, A, B,  3, 16, 0xD4EF3085);
    HH(B, C, D, A,  6, 23, 0x04881D05);
    HH(A, B, C, D,  9,  4, 0xD9D4D039);
    HH(D, A, B, C, 12, 11, 0xE6DB99E5);
    HH(C, D, A, B, 15, 16, 0x1FA27CF8);
    HH(B, C, D, A,  2, 23, 0xC4AC5665);

    II(A, B, C, D,  0,  6, 0xF4292244);
    II(D, A, B, C,  7, 10, 0x432AFF97);
    II(C, D, A, B, 14, 15, 0xAB9423A7);
    II(B, C, D, A,  5, 21, 0xFC93A039);
    II(A, B, C, D, 12,  6, 0x655B59C3);
    II(D, A, B, C,  3, 10, 0x8F0CCC92);
    II(C, D, A, B, 10, 15, 0xFFEFF47D);
    II(B, C, D, A,  1, 21, 0x85845DD1);
    II(A, B, C, D,  8,  6, 0x6FA87E4F);
    II(D, A, B, C, 15, 10, 0xFE2CE6E0);
    II(C, D, A, B,  6, 15, 0xA3014314);
    II(B, C, D, A, 13, 21, 0x4E0811A1);
    II(A, B, C, D,  4,  6, 0xF7537E82);
    II(D, A, B, C, 11, 10, 0xBD3AF235);
    II(C, D, A, B,  2, 15, 0x2AD7D2BB);
    II(B, C, D, A,  9, 21, 0xEB86D391);

    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
}

void MD5_update(md5_context *ctx, BYTE *input, WORD length) {
    WORD left, fill;

    if (!length) return;

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += length;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < length) ctx->total[1]++;

    if (left && length >= fill) {
        memcpy((void*)(ctx->buffer + left), (void*)input, fill);
        MD5_process(ctx, ctx->buffer);
        length -= fill;
        input  += fill;
        left = 0;
    }

    while (length >= 64) {
        MD5_process(ctx, input);
        length -= 64;
        input  += 64;
    }

    if (length) {
        memcpy((void*)(ctx->buffer + left), (void*)input, length);
    }
}

static BYTE md5_padding[64] =
{
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void MD5_finish(md5_context *ctx, BYTE digest[16]) {
    WORD last, padn;
    WORD high, low;
    BYTE msglen[8];

    high = (ctx->total[0] >> 29)
         | (ctx->total[1] <<  3);
    low  = (ctx->total[0] <<  3);

    PUT_WORD(low,  msglen, 0);
    PUT_WORD(high, msglen, 4);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    MD5_update(ctx, md5_padding, padn);
    MD5_update(ctx, msglen, 8);

    PUT_WORD(ctx->state[0], digest,  0);
    PUT_WORD(ctx->state[1], digest,  4);
    PUT_WORD(ctx->state[2], digest,  8);
    PUT_WORD(ctx->state[3], digest, 12);
}

__device__ void cuda_brute_force_attack(char *hash, char *result) {
    md5_context ctx;
    BYTE md5sum[16];
    char md5String[33], password[6];
    int i, j, k, l, m, t;

    t = 1;
    for (i = 32; i < 127; i++) {
        for (j = 32; j < 127; j++) {
            for (k = 32; k < 127; k++) {
                for (l = 32; l < 127; l++) {
                    for (m = 32; m < 127; m++) {
                        password[0] = i;
                        password[1] = j;
                        password[2] = k;
                        password[3] = l;
                        password[4] = m;
                        password[5] = '\0';

                        MD5_starts(&ctx);
                        MD5_update(&ctx, (BYTE *)password, strlen(password));
                        MD5_finish(&ctx, md5sum);
                        for (int n = 0; n < 16; n++) {
                            sprintf(&md5String[n+n], "%02x", md5sum[n]);
                        }
                        if (!strcmp(md5String, hash)) {
                            strcpy(result, password);
                            t = 0;
                            break;
                        }
                    }
                    if (!t) break;
                }
                if (!t) break;
            }
            if (!t) break;
        }
        if (!t) break;
    }
    if (t != 0) {
        strcpy(result, "Password not found!");
    }
}

void dictionary_attack(char *hash) {
    // Dictionary attack implementation goes here
}

void brute_force_attack(char *hash) {
    int size = sizeof(char) * (strlen(hash) + 1);
    char *dev_hash, *dev_result;
    char *result = (char*)malloc(size);

    cudaMalloc((void**)&dev_hash, size);
    cudaMalloc((void**)&dev_result, size);

    cudaMemcpy(dev_hash, hash, size, cudaMemcpyHostToDevice);

    cuda_brute_force_attack<<<1, 1>>>(dev_hash, dev_result);

    cudaMemcpy(result, dev_result, size, cudaMemcpyDeviceToHost);

    std::cout << "Result: " << result << std::endl;

    free(result);
    cudaFree(dev_hash);
    cudaFree(dev_result);
}

int main() {
    char hash[33];
    int option;

    std::cout << "辞書攻撃は1を。総当たり攻撃は2を入力してください: ";
    std::cin >> option;

    if (option == 1) {
        std::cout << "ハッシュ値を入力してください: ";
        std::cin >> hash;
        dictionary_attack(hash);
    } else if (option == 2) {
        std::cout << "ハッシュ値を入力してください: ";
        std::cin >> hash;
        brute_force_attack(hash);
    } else {
        std::cout << "無効なオプションです。" << std::endl;
    }

    return 0;
}
