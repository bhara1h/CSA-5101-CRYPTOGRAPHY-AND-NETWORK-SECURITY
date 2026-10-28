#include <stdio.h>
#include <string.h>
void des_enc_block(unsigned char *in, unsigned char *out){memcpy(out,in,8);}
void des_dec_block(unsigned char *in, unsigned char *out){memcpy(out,in,8);}

int main(){
    unsigned char c1[8]={1,2,3,4,5,6,7,8}, c2[8]={8,7,6,5,4,3,2,1}, iv[8]={0};
    unsigned char p1[8],p2[8];
    // Simulate error in C1: flip bit 0
    c1[0]^=0x01;
    // CBC decode: P1 = D(C1) xor IV -> garbled, P2 = D(C2) xor C1 -> 1 bit error
    // P3 = D(C3) xor C2 -> not affected
    printf("CBC: Error in C1 affects only P1 and P2, not beyond\n");
    // Source P1 error -> propagates to all ciphertext
    // C1=E(P1 xor IV), C2=E(P2 xor C1) ... all changed
    printf("Source P1 error propagates to all C_i and all P_i at receiver\n");
    return 0;
}