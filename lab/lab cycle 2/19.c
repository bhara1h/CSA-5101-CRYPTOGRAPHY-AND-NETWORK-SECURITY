#include <stdio.h>
#include <string.h>
void des_enc(unsigned char *in, unsigned char *out, unsigned char *k);
void des_dec(unsigned char *in, unsigned char *out, unsigned char *k);

void tdes_enc(unsigned char *in, unsigned char *out, unsigned char *k1, unsigned char *k2, unsigned char *k3){
    unsigned char t1[8],t2[8];
    des_enc(in,t1,k1); des_dec(t1,t2,k2); des_enc(t2,out,k3);
}
void tdes_dec(unsigned char *in, unsigned char *out, unsigned char *k1, unsigned char *k2, unsigned char *k3){
    unsigned char t1[8],t2[8];
    des_dec(in,t1,k3); des_enc(t1,t2,k2); des_dec(t2,out,k1);
}
int main(){
    unsigned char k1[8]={1,2,3,4,5,6,7,8},k2[8]={8,7,6,5,4,3,2,1},k3[8]={1,2,3,4,5,6,7,8};
    unsigned char iv[8]={0,0,0,0,0,0,0,0};
    unsigned char pt[16]="Hello123Hello123";
    unsigned char ct[16], dec[16], prev[8];
    memcpy(prev,iv,8);
    for(int i=0;i<16;i+=8){
        unsigned char x[8]; for(int j=0;j<8;j++) x[j]=pt[i+j]^prev[j];
        tdes_enc(x,ct+i,k1,k2,k3); memcpy(prev,ct+i,8);
    }
    memcpy(prev,iv,8);
    for(int i=0;i<16;i+=8){
        unsigned char t[8]; tdes_dec(ct+i,t,k1,k2,k3);
        for(int j=0;j<8;j++) dec[i+j]=t[j]^prev[j];
        memcpy(prev,ct+i,8);
    }
    return 0;
}