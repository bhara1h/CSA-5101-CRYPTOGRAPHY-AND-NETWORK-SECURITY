#include <stdio.h>
int S0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int S1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

unsigned char sdes_enc(unsigned char pt, int key){
    int k1=0,k2=0; // derive 8-bit k1,k2 from 10-bit key - omitted for brevity, use standard SDES keygen
    // initial perm, f with S0,S1, switch, f, inv perm
    return pt ^ (key & 0xFF); // placeholder for real SDES logic - replace with full SDES function
}
int main(){
    unsigned char iv=0xAA; // 10101010
    int key=0x1FD; // 0111111101 = 509? 0b01 1111 1101 = 253
    unsigned char pt[2]={0x01,0x23};
    unsigned char ct[2], dec[2];
    unsigned char prev=iv;
    for(int i=0;i<2;i++){ ct[i]=sdes_enc(pt[i]^prev,key); prev=ct[i]; }
    printf("CT: %02X %02X expected F4 0B\n",ct[0],ct[1]);
    prev=iv;
    for(int i=0;i<2;i++){ unsigned char t=sdes_enc(ct[i],key); dec[i]=t^prev; prev=ct[i]; }
    return 0;
}