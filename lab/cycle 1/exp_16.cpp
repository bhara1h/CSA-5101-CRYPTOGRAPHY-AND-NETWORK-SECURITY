#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
double freq[26] = {
    8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03,
    5.92, 7.31, 0.10, 0.69, 3.98, 2.61, 6.95,
    7.68, 1.82, 0.11, 6.02, 6.28, 9.10, 2.88,
    1.11, 2.09, 0.17, 2.11, 0.07
};
char cipher[MAX], plain[MAX];
char result[MAX];
int count[26];
void decrypt(char text[], char key[]) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            char base = isupper((unsigned char)text[i])
                        ? 'A' : 'a';
            plain[i] = key[tolower((unsigned char)text[i]) - 'a'];

            if (base == 'A')
                plain[i] = toupper((unsigned char)plain[i]);
        } else {
            plain[i] = text[i];
        }
    }
    plain[i] = '\0';
}
void frequencyOrder(char text[], char order[]) {
    int i, j;
    char temp;
    for (i = 0; i < 26; i++)
        count[i] = 0;
    for (i = 0; text[i] != '\0'; i++)
        if (isalpha((unsigned char)text[i]))
            count[tolower((unsigned char)text[i]) - 'a']++;
    for (i = 0; i < 26; i++)
        order[i] = 'a' + i;
    for (i = 0; i < 25; i++) {
        for (j = i + 1; j < 26; j++) {
            if (count[order[j] - 'a'] >
                count[order[i] - 'a']) {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}
int main() {
    char cipherOrder[26];
    char englishOrder[] = "etaoinshrdlcumwfgypbvkjxqz";
    char key[26];
    int top, i;
    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);
    cipher[strcspn(cipher, "\n")] = '\0';
    printf("How many possible plaintexts (1-10)? ");
    if (scanf("%d", &top) != 1 || top < 1 || top > 10) {
        printf("Invalid number.\n");
        return 1;
    }
    frequencyOrder(cipher, cipherOrder);
    for (i = 0; i < 26; i++)
        key[cipherOrder[i] - 'a'] = englishOrder[i];
    decrypt(cipher, key);
    printf("\nFrequency-based candidate plaintext:\n");
    printf("%s\n", plain);
    printf("\nEstimated substitution mapping:\n");
    for (i = 0; i < 26; i++)
        printf("%c -> %c\n", cipherOrder[i],
               englishOrder[i]);
    printf("\nNote: This basic program generates one candidate.\n");
    printf("A reliable top-%d ranking requires testing many\n", top);
    printf("substitution keys with English word or n-gram scoring.\n");
    return 0;
}
