#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 8
int P10[10] = {3,5,2,7,4,10,1,9,8,6};
int P8[8] = {6,3,7,4,8,5,10,9};
int IP[8] = {2,6,3,1,4,8,5,7};
int IP_INV[8] = {4,1,3,5,7,2,8,6};
int EP[8] = {4,1,2,3,2,3,4,1};
int P4[4] = {2,4,3,1};
int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};
int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};
void permute(int *in, int *out, int *table, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = in[table[i] - 1];
}
void leftShift(int *a, int n, int shift)
{
    int temp[5];
    for (int i = 0; i < n; i++)
        temp[i] = a[(i + shift) % n];
    for (int i = 0; i < n; i++)
        a[i] = temp[i];
}
void generateKeys(int key[10], int K1[8], int K2[8])
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
void xorBits(int *a, int *b, int *out, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = a[i] ^ b[i];
}
void fk(int bits[8], int key[8])
{
    int L[4], R[4], expanded[8], x[8], s[4], p4[4];
    for (int i = 0; i < 4; i++) {
        L[i] = bits[i];
        R[i] = bits[i + 4];
    }
    permute(R, expanded, EP, 8);
    xorBits(expanded, key, x, 8);
    int row = x[0] * 2 + x[3];
    int col = x[1] * 2 + x[2];
    int val = S0[row][col];
    s[0] = (val >> 1) & 1;
    s[1] = val & 1;
    row = x[4] * 2 + x[7];
    col = x[5] * 2 + x[6];
    val = S1[row][col];
    s[2] = (val >> 1) & 1;
    s[3] = val & 1;
    permute(s, p4, P4, 4);
    for (int i = 0; i < 4; i++) {
        bits[i] = L[i] ^ p4[i];
        bits[i + 4] = R[i];
    }
}
void swapHalves(int bits[8])
{
    for (int i = 0; i < 4; i++) {
        int temp = bits[i];
        bits[i] = bits[i + 4];
        bits[i + 4] = temp;
    }
}
void sdes(int input[8], int output[8], int K1[8], int K2[8])
{
    int bits[8];
    permute(input, bits, IP, 8);
    fk(bits, K1);
    swapHalves(bits);
    fk(bits, K2);
    permute(bits, output, IP_INV, 8);
}
void ctrMode(int input[], int output[], int n,
             int K1[8], int K2[8])
{
    int counter[8] = {0};
    int stream[8];
    for (int block = 0; block < n / 8; block++) {
        sdes(counter, stream, K1, K2);
        for (int j = 0; j < 8; j++)
            output[block * 8 + j] =
                input[block * 8 + j] ^ stream[j];
        for (int j = 7; j >= 0; j--) {
            if (++counter[j] <= 1)
                break;
            counter[j] = 0;
        }
    }
}
void printBits(int bits[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d", bits[i]);
        if ((i + 1) % 8 == 0 && i + 1 < n)
            printf(" ");
    }
    printf("\n");
}
int main(void)
{
    int key[10], plaintext[24], ciphertext[24], decrypted[24];
    int K1[8], K2[8];
    printf("Enter 10-bit key: ");
    for (int i = 0; i < 10; i++) {
        if (scanf("%1d", &key[i]) != 1 || key[i] > 1)
            return 1;
    }
    printf("Enter 24-bit plaintext: ");
    for (int i = 0; i < 24; i++) {
        if (scanf("%1d", &plaintext[i]) != 1 ||
            plaintext[i] > 1)
            return 1;
    }
    generateKeys(key, K1, K2);
    ctrMode(plaintext, ciphertext, 24, K1, K2);
    ctrMode(ciphertext, decrypted, 24, K1, K2);
    printf("\nInitial Counter: 00000000\n");
    printf("Ciphertext: ");
    printBits(ciphertext, 24);
    printf("Decrypted plaintext: ");
    printBits(decrypted, 24);
    return 0;
}