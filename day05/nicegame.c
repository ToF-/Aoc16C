#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define LINE_MAX 100

typedef union uwb {
    unsigned w;
    unsigned char b[4];
} MD5union;

typedef unsigned DigestArray[4];

unsigned func0(unsigned abcd[]) {
    return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}

unsigned func1(unsigned abcd[]) {
    return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}

unsigned func2(unsigned abcd[]) {
    return  abcd[1] ^ abcd[2] ^ abcd[3];
}

unsigned func3(unsigned abcd[]) {
    return abcd[2] ^ (abcd[1] | ~abcd[3]);
}

typedef unsigned(*DgstFctn)(unsigned a[]);

unsigned *calctable(unsigned *k)
{
    double s, pwr;
    int i;

    pwr = pow(2.0, 32);
    for (i = 0; i<64; i++) {
        s = fabs(sin(1.0 + i));
        k[i] = (unsigned)(s * pwr);
    }
    return k;
}

unsigned rol(unsigned r, short N)
{
    unsigned  mask1 = (1 << N) - 1;
    return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
}

unsigned* Algorithms_Hash_MD5(const char *msg, int mlen)
{
    static DigestArray h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
    static DgstFctn ff[] = { &func0, &func1, &func2, &func3 };
    static short M[] = { 1, 5, 3, 7 };
    static short O[] = { 0, 1, 5, 0 };
    static short rot0[] = { 7, 12, 17, 22 };
    static short rot1[] = { 5, 9, 14, 20 };
    static short rot2[] = { 4, 11, 16, 23 };
    static short rot3[] = { 6, 10, 15, 21 };
    static short *rots[] = { rot0, rot1, rot2, rot3 };
    static unsigned kspace[64];
    static unsigned *k;

    static DigestArray h;
    DigestArray abcd;
    DgstFctn fctn;
    short m, o, g;
    unsigned f;
    short *rotn;
    union {
        unsigned w[16];
        char     b[64];
    }mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;

    if (k == NULL) k = calctable(kspace);

    for (q = 0; q<4; q++) h[q] = h0[q];

    {
        grps = 1 + (mlen + 8) / 64;
        msg2 = (unsigned char*)malloc(64 * grps);
        memcpy(msg2, msg, mlen);
        msg2[mlen] = (unsigned char)0x80;
        q = mlen + 1;
        while (q < 64 * grps) { msg2[q] = 0; q++; }
        {
            MD5union u;
            u.w = 8 * mlen;
            q -= 8;
            memcpy(msg2 + q, &u.w, 4);
        }
    }

    for (grp = 0; grp<grps; grp++)
    {
        memcpy(mm.b, msg2 + os, 64);
        for (q = 0; q<4; q++) abcd[q] = h[q];
        for (p = 0; p<4; p++) {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p]; o = O[p];
            for (q = 0; q<16; q++) {
                g = (m*q + o) % 16;
                f = abcd[1] + rol(abcd[0] + fctn(abcd) + k[q + 16 * p] + mm.w[g], rotn[q % 4]);

                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p = 0; p<4; p++)
            h[p] += abcd[p];
        os += 64;
    }
    return h;
}

const char* GetMD5String(const char *msg, int mlen, char *dest) {
    strcpy(dest, "");
    int j, k;
    unsigned *d = Algorithms_Hash_MD5(msg, strlen(msg));
    MD5union u;
    for (j = 0; j<4; j++) {
        u.w = d[j];
        char* s[8];
        sprintf(s, "%02x%02x%02x%02x", u.b[0], u.b[1], u.b[2], u.b[3]);
        strcat(dest, s);
    }

    return dest;
}
int valid(char *p) {
    int result = 1;
    for(int i=0; i<5; i++) {
        result &= (*p++ == '0');
    }
    return result;
}

int main(int argc, char* argv[])
{
    char line[LINE_MAX];
    char password[9];
    char value[40];
    int count = 0;
    memset(password, 0, 9);
    if (argc < 2) {
        printf("missing argument");
        return 1;
    }
    for(int i=0; i<99999999; i++) {
        if(i%1000000 == 0) printf("%10d\n",i);
        sprintf(line,"%s%d", argv[1], i);
        GetMD5String(line, 40, value);
        if(valid(value)) {
            printf("%s\n", value);
            if (value[5] >= '0' && value[5] <= '7') {
                int pos = value[5] - '0';
                if(password[pos] == '\0') 
                {
                    password[pos] = value[6];
                    printf("found %c in pos %d\n", value[6], pos);
                    int full = 0;
                    for(int i=0; i < 8; i++)
                        if(password[i] != 0)
                            full++;
                    if(full == 8)
                        break;
                }
            }
        }
    }
    printf("%s\n", password);
    return 0;
}
