#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char text[100], key[50];
    int i, j = 0, shift;
    char cipher;
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    printf("\nEncryption Process:\n");
    printf("-------------------\n");
    printf("Plaintext\tKey\tShift\tCipher\n");
    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            printf(" \t\t-\t-\t \n");
            continue;
        }
        text[i] = toupper(text[i]);
        key[j] = toupper(key[j]);

        shift = key[j] - 'A';
        cipher = (text[i] - 'A' + shift) % 26 + 'A';

        printf("%c\t\t%c\t%d\t%c\n",
               text[i], key[j], shift, cipher);

        text[i] = cipher;
        j++;
        if (key[j] == '\0')
            j = 0;
    }
    printf("\nFinal Encrypted Text: %s", text);
    return 0;
}