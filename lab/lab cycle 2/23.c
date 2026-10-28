#include <stdio.h>
unsigned char sdes_enc_ctr(unsigned char in, int key);
int main(){
    int key=253; // 0111111101
    unsigned char ctr=0x00;
    unsigned char pt[3]={0x01,0x02,0x04};
    unsigned char ct[3];
    for(int i=0;i<3;i++){
        unsigned char ks=sdes_enc_ctr(ctr+i,key);
        ct[i]=pt[i]^ks;
    }
    printf("CT: %02X %02X %02X expected 38 4F 32\n",ct[0],ct[1],ct[2]);
    return 0;
}
unsigned char sdes_enc_ctr(unsigned char in, int key){ return in ^ (key & 0xFF); }