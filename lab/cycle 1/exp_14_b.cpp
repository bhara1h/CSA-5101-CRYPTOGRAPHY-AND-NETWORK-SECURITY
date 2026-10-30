#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char plain[] = "send more money";
    char target[] = "cash not needed";
    char cipher[100], compact[100], key2[100];
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};
    int i, j = 0, n = 0, k = 0;
    for (i = 0; plain[i] != '\0'; i++) {
        if (plain[i] == ' ') {
            cipher[n++] = ' ';
        } else {
            int p = tolower((unsigned char)plain[i]) - 'a';
            int c = (p + key[j++]) % 26;
            cipher[n++] = c + 'a';
            compact[k++] = c + 'a';
        }
    }
    cipher[n] = '\0';
    compact[k] = '\0';
    printf("Part (a) Ciphertext: %s\n", cipher);
    j = 0;
    for (i = 0; target[i] != '\0'; i++) {
        if (target[i] != ' ') {
            int c = compact[j] - 'a';
            int p = tolower((unsigned char)target[i]) - 'a';
            key2[j] = (c - p + 26) % 26 + 'a';
            j++;
        }
    }
    key2[j] = '\0';
    printf("Part (b) Required key: %s\n", key2);
    return 0;
}
