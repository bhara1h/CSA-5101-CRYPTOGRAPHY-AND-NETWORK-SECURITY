#include <stdio.h>
int modpow(int a,int e,int n){int r=1;while(e){if(e&1)r=(r*a)%n;a=(a*a)%n;e>>=1;}return r;}
int main(){
    int e=31,n=3599;
    int ct[26];
    for(int i=0;i<26;i++) ct[i]=modpow(i,e,n);
    printf("Attacker builds table of 26 ciphertexts using public key\n");
    printf("Any ciphertext can be decrypted by table lookup - no factoring needed\n");
    printf("Use OAEP padding\n");
    return 0;
}