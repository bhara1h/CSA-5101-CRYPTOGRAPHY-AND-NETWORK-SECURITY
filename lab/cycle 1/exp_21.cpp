#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 8
#define MAX_SIZE 256
void encryptBlock(const unsigned char in[],
                  unsigned char out[])
{
    int i;
    for (i = 0; i < BLOCK_SIZE; i++)
        out[i] = in[i] ^ 0x5A;
}
void decryptBlock(const unsigned char in[],
                  unsigned char out[])
{
    encryptBlock(in, out);
}
int padMessage(unsigned char data[], int len)
{
    int paddedLen = ((len / BLOCK_SIZE) + 1) * BLOCK_SIZE;

    data[len] = 0x80;

    for (int i = len + 1; i < paddedLen; i++)
        data[i] = 0x00;

    return paddedLen;
}
void printHex(const char *label, unsigned char data[], int len)
{
    printf("%s", label);
    for (int i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("\n");
}
int main(void)
{
    unsigned char plaintext[MAX_SIZE];
    unsigned char ecb[MAX_SIZE], cbc[MAX_SIZE], cfb[MAX_SIZE];
    unsigned char temp[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE] = {
        'I', 'N', 'I', 'T', 'V', 'E', 'C', 'T'
    };
    int len, paddedLen;
    printf("Enter plaintext (maximum 200 characters): ");
    if (fgets((char *)plaintext, 201, stdin) == NULL)
        return 1;
    len = (int)strlen((char *)plaintext);
    if (len > 0 && plaintext[len - 1] == '\n')
        plaintext[--len] = '\0';
    if (len == 0) {
        printf("Plaintext must not be empty.\n");
        return 1;
    }
    paddedLen = padMessage(plaintext, len);
    for (int i = 0; i < paddedLen; i += BLOCK_SIZE)
        encryptBlock(plaintext + i, ecb + i);
    for (int i = 0; i < paddedLen; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            unsigned char previous =
                (i == 0) ? iv[j] : cbc[i - BLOCK_SIZE + j];
            temp[j] = plaintext[i + j] ^ previous;
        }
        encryptBlock(temp, cbc + i);
    }
    for (int i = 0; i < paddedLen; i += BLOCK_SIZE) {
        unsigned char stream[BLOCK_SIZE];

        encryptBlock((i == 0) ? iv : cfb + i - BLOCK_SIZE,
                     stream);

        for (int j = 0; j < BLOCK_SIZE; j++)
            cfb[i + j] = plaintext[i + j] ^ stream[j];
    }
    printf("\nOriginal plaintext: %s\n", (char *)plaintext);
    printf("Original length: %d bytes\n", len);
    printf("Padded length: %d bytes\n\n", paddedLen);
    printHex("Padded plaintext: ", plaintext, paddedLen);
    printHex("ECB ciphertext:   ", ecb, paddedLen);
    printHex("CBC ciphertext:   ", cbc, paddedLen);
    printHex("CFB ciphertext:   ", cfb, paddedLen);
    return 0;
}
