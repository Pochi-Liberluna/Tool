#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>

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

struct sha256_context {
    WORD total[2];
    WORD state[8];
    BYTE buffer[64];
};

const WORD K[64] = {
    0x428A2F98UL, 0x71374491UL, 0xB5C0FBCFUL, 0xE9B5DBA5UL,
    0x3956C25BUL, 0x59F111F1UL, 0x923F82A4UL, 0xAB1C5ED5UL,
    0xD807AA98UL, 0x12835B01UL, 0x243185BEUL, 0x550C7DC3UL,
    0x72BE5D74UL, 0x80DEB1FEUL, 0x9BDC06A7UL, 0xC19BF174UL,
    0xE49B69C1UL, 0xEFBE4786UL, 0x0FC19DC6UL, 0x240CA1CCUL,
    0x2DE92C6FUL, 0x4A7484AAUL, 0x5CB0A9DCUL, 0x76F988DAUL,
    0x983E5152UL, 0xA831C66DUL, 0xB00327C8UL, 0xBF597FC7UL,
    0xC6E00BF3UL, 0xD5A79147UL, 0x06CA6351UL, 0x14292967UL,
    0x27B70A85UL, 0x2E1B2138UL, 0x4D2C6DFCUL, 0x53380D13UL,
    0x650A7354UL, 0x766A0ABBUL, 0x81C2C92EUL, 0x92722C85UL,
    0xA2BFE8A1UL, 0xA81A664BUL, 0xC24B8B70UL, 0xC76C51A3UL,
    0xD192E819UL, 0xD6990624UL, 0xF40E3585UL, 0x106AA070UL,
    0x19A4C116UL, 0x1E376C08UL, 0x2748774CUL, 0x34B0BCB5UL,
    0x391C0CB3UL, 0x4ED8AA4AUL, 0x5B9CCA4FUL, 0x682E6FF3UL,
    0x748F82EEUL, 0x78A5636FUL, 0x84C87814UL, 0x8CC70208UL,
    0x90BEFFFAUL, 0xA4506CEBUL, 0xBEF9A3F7UL, 0xC67178F2UL
};

#define SHR(x, n) (((x) & 0xFFFFFFFFUL) >> (n))
#define ROTR(x, n) (SHR((x), (n)) | ((x) << (32 - (n))))
#define S0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define S1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))
#define CH(x, y, z) ((x & y) ^ ((~x) & z))
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

#define EP0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define EP1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

void SHA256_starts(sha256_context *ctx) {
    ctx->total[0] = 0;
    ctx->total[1] = 0;

    ctx->state[0] = 0x6A09E667UL;
    ctx->state[1] = 0xBB67AE85UL;
    ctx->state[2] = 0x3C6EF372UL;
    ctx->state[3] = 0xA54FF53AUL;
    ctx->state[4] = 0x510E527FUL;
    ctx->state[5] = 0x9B05688CUL;
    ctx->state[6] = 0x1F83D9ABUL;
    ctx->state[7] = 0x5BE0CD19UL;
}

void SHA256_process(sha256_context *ctx, BYTE data[64]) {
    WORD state[8];
    WORD W[64];
    WORD temp1, temp2;
    WORD A, B, C, D, E, F, G, H;

    GET_WORD(W[0],  data,  0);
    GET_WORD(W[1],  data,  4);
    GET_WORD(W[2],  data,  8);
    GET_WORD(W[3],  data, 12);
    GET_WORD(W[4],  data, 16);
    GET_WORD(W[5],  data, 20);
    GET_WORD(W[6],  data, 24);
    GET_WORD(W[7],  data, 28);
    GET_WORD(W[8],  data, 32);
    GET_WORD(W[9],  data, 36);
    GET_WORD(W[10], data, 40);
    GET_WORD(W[11], data, 44);
    GET_WORD(W[12], data, 48);
    GET_WORD(W[13], data, 52);
    GET_WORD(W[14], data, 56);
    GET_WORD(W[15], data, 60);

    for (int i = 16; i < 64; i++) {
        W[i] = SIG1(W[i-2]) + W[i-7] + SIG0(W[i-15]) + W[i-16];
    }

    memcpy(state, ctx->state, sizeof(ctx->state));

    for (int i = 0; i < 64; i++) {
        temp1 = state[7] + EP1(state[4]) + CH(state[4], state[5], state[6]) + K[i] + W[i];
        temp2 = EP0(state[0]) + MAJ(state[0], state[1], state[2]);
        state[7] = state[6];
        state[6] = state[5];
        state[5] = state[4];
        state[4] = state[3] + temp1;
        state[3] = state[2];
        state[2] = state[1];
        state[1] = state[0];
        state[0] = temp1 + temp2;
    }

    for (int i = 0; i < 8; i++) {
        ctx->state[i] += state[i];
    }
}

void SHA256_update(sha256_context *ctx, BYTE *input, WORD length) {
    WORD left, fill;

    if (!length) return;

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += length;
    ctx->total[0] &= 0xFFFFFFFFUL;

    if (ctx->total[0] < length) ctx->total[1]++;

    if (left && length >= fill) {
        memcpy((void*)(ctx->buffer + left), (void*)input, fill);
        SHA256_process(ctx, ctx->buffer);
        length -= fill;
        input  += fill;
        left = 0;
    }

    while (length >= 64) {
        SHA256_process(ctx, input);
        length -= 64;
        input  += 64;
    }

    if (length) {
        memcpy((void*)(ctx->buffer + left), (void*)input, length);
    }
}

static BYTE sha256_padding[64] =
{
 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void SHA256_finish(sha256_context *ctx, BYTE digest[32]) {
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

    SHA256_update(ctx, sha256_padding, padn);
    SHA256_update(ctx, msglen, 8);

    PUT_WORD(ctx->state[0], digest,  0);
    PUT_WORD(ctx->state[1], digest,  4);
    PUT_WORD(ctx->state[2], digest,  8);
    PUT_WORD(ctx->state[3], digest, 12);
    PUT_WORD(ctx->state[4], digest, 16);
    PUT_WORD(ctx->state[5], digest, 20);
    PUT_WORD(ctx->state[6], digest, 24);
    PUT_WORD(ctx->state[7], digest, 28);
}

int main(int argc, char *argv[]) {
    sha256_context ctx;
    BYTE sha256sum[32];
    std::string sha256String;
    char tmp[MAX_BUFFER_SIZE];
    int i, j, t;

    if (argc <= 2) {
        std::cout << "Usage: " << argv[0] << " <hash> <file_name>\n";
        return 1;
    }

    std::ifstream file(argv[2]);
    if (!file) {
        std::cout << "Failed to open file.\n";
        return 1;
    }

    t = 1;
    while (file.getline(tmp, MAX_BUFFER_SIZE)) {
        tmp[strcspn(tmp, "\r\n")] = 0;
        SHA256_starts(&ctx);
        SHA256_update(&ctx, (BYTE *)tmp, strlen(tmp));
        SHA256_finish(&ctx, sha256sum);
        for (j = 0; j < 32; j++) {
            sha256String += "0123456789abcdef"[sha256sum[j] >> 4];
            sha256String += "0123456789abcdef"[sha256sum[j] & 0x0F];
        }
        if (sha256String == argv[1]) {
            std::cout << "Hash found: " << tmp << '\n';
            t = 0;
            break;
        }
        sha256String.clear();
    }
    if (t != 0) {
        std::cout << "Hash not found!\n";
    }

    file.close();

    return 0;
}
