#include <stdio.h>
#include <string.h>
int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[8]   = {6, 3, 7, 4, 8, 5, 10, 9};
int IP[8]   = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_INV[8] = {4, 1, 3, 5, 7, 2, 8, 6};
int EP[8]   = {4, 1, 2, 3, 2, 3, 4, 1};
int P4[4]   = {2, 4, 3, 1};
int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};
int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};
void permute(const int *in, int *out, const int *table, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = in[table[i] - 1];
}
void leftShift(int *bits, int n, int shift)
{
    int temp[5];
    for (int i = 0; i < n; i++)
        temp[i] = bits[(i + shift) % n];
    for (int i = 0; i < n; i++)
        bits[i] = temp[i];
}
void generateKeys(const int key[10], int K1[8], int K2[8])
{
    int p[10], L[5], R[5], combined[10];
    permute(key, p, P10, 10);
    for (int i = 0; i < 5; i++) {
        L[i] = p[i];
        R[i] = p[i + 5];
    }
    leftShift(L, 5, 1);
    leftShift(R, 5, 1);
    for (int i = 0; i < 5; i++) {
        combined[i] = L[i];
        combined[i + 5] = R[i];
    }
    permute(combined, K1, P8, 8);
    leftShift(L, 5, 2);
    leftShift(R, 5, 2);
    for (int i = 0; i < 5; i++) {
        combined[i] = L[i];
        combined[i + 5] = R[i];
    }
    permute(combined, K2, P8, 8);
}
void xorBits(const int *a, const int *b, int *out, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = a[i] ^ b[i];
}
void fk(int *bits, const int *key)
{
    int L[4], R[4], expanded[8], x[8], sInput[4];
    int sOut[4], p4[4], temp[8];
    for (int i = 0; i < 4; i++) {
        L[i] = bits[i];
        R[i] = bits[i + 4];
    }
    permute(R, expanded, EP, 8);
    xorBits(expanded, key, x, 8);
    int row = x[0] * 2 + x[3];
    int col = x[1] * 2 + x[2];
    int value = S0[row][col];
    sInput[0] = (value >> 1) & 1;
    sInput[1] = value & 1;
    row = x[4] * 2 + x[7];
    col = x[5] * 2 + x[6];
    value = S1[row][col];
    sInput[2] = (value >> 1) & 1;
    sInput[3] = value & 1;
    permute(sInput, p4, P4, 4);
    xorBits(L, p4, temp, 4);
    for (int i = 0; i < 4; i++) {
        bits[i] = temp[i];
        bits[i + 4] = R[i];
    }
}
void swapHalves(int *bits)
{
    for (int i = 0; i < 4; i++) {
        int temp = bits[i];
        bits[i] = bits[i + 4];
        bits[i + 4] = temp;
    }
}
void sdes(const int input[8], int output[8],
          const int K1[8], const int K2[8], int decrypt)
{
    int bits[8], temp[8];
    permute(input, bits, IP, 8);
    fk(bits, decrypt ? K2 : K1);
    swapHalves(bits);
    fk(bits, decrypt ? K1 : K2);
    permute(bits, output, IP_INV, 8);
}
void printBits(const int *bits, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d", bits[i]);
        if ((i + 1) % 4 == 0 && i + 1 < n)
            printf(" ");
    }
}
int main(void)
{
    int key[10], plaintext[16], iv[8] = {1,0,1,0,1,0,1,0};
    int K1[8], K2[8], cipher[16], recovered[16];
    int block[8], temp[8], result[8];
    printf("Enter 10-bit key (e.g. 0111111101): ");
    for (int i = 0; i < 10; i++)
        if (scanf("%1d", &key[i]) != 1 || key[i] > 1)
            return 1;
    printf("Enter 16-bit plaintext (e.g. 0000000100100011): ");
    for (int i = 0; i < 16; i++)
        if (scanf("%1d", &plaintext[i]) != 1 || plaintext[i] > 1)
            return 1;
    generateKeys(key, K1, K2);
    for (int b = 0; b < 2; b++) {
        for (int j = 0; j < 8; j++) {
            int previous = (b == 0) ? iv[j] : cipher[(b - 1) * 8 + j];
            block[j] = plaintext[b * 8 + j] ^ previous;
        }
        sdes(block, result, K1, K2, 0);
        for (int j = 0; j < 8; j++)
            cipher[b * 8 + j] = result[j];
    }
    for (int b = 0; b < 2; b++) {
        for (int j = 0; j < 8; j++)
            block[j] = cipher[b * 8 + j];
        sdes(block, result, K1, K2, 1);
        for (int j = 0; j < 8; j++) {
            int previous = (b == 0) ? iv[j] : cipher[(b - 1) * 8 + j];
            recovered[b * 8 + j] = result[j] ^ previous;
        }
    }
    printf("\nInitialization Vector: ");
    printBits(iv, 8);
    printf("\nCiphertext: ");
    printBits(cipher, 16);
    printf("\nDecrypted plaintext: ");
    printBits(recovered, 16);
    printf("\n");
    return 0;
}