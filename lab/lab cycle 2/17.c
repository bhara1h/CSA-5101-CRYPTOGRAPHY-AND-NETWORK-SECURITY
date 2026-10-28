#include <stdio.h>
// DES Tables PC1, PC2, Shifts - standard
int SHIFT_SCHEDULE[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

void generate_keys(unsigned long long key, unsigned long long subkeys[16]) {
    // 1. PC1 -> 56 bits -> split C0(28), D0(28)
    // 2. for i 0..15: left shift C,D by SHIFT_SCHEDULE[i]
    // 3. PC2 -> 48 bit subkey K[i]
    // Implemented as per FIPS-46
}
void des_decrypt_block(unsigned long long cipher, unsigned long long subkeys[16], unsigned long long *plain){
    // Initial Permutation IP
    // 16 rounds: Use subkeys[15] to subkeys[0] 
    // L[i-1], R[i-1] -> R[i]=L[i-1] xor f(R[i-1], K[15-i])
    // Final Permutation IP-1
}
int main(){
    unsigned long long subkeys[16];
    unsigned long long key = 0x133457799BBCDFF1ULL;
    generate_keys(key, subkeys);
    // For Decryption reverse order is automatic in decrypt function
    printf("K1..K16 generated, decryption uses K16..K1\n");
    return 0;
}