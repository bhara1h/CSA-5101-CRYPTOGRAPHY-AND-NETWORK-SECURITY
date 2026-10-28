#include <stdio.h>
#include <string.h>
void pad(unsigned char *buf, int data_len, int block_size, int *out_len){
    int pad_len = block_size - (data_len % block_size);
    buf[data_len]=0x80;
    for(int i=1;i<pad_len;i++) buf[data_len+i]=0x00;
    if(pad_len==0){
        for(int i=0;i<block_size;i++) buf[data_len+i]=(i==0?0x80:0x00);
        *out_len=data_len+block_size;
    }else{
        *out_len=data_len+pad_len;
    }
}
int main(){
    unsigned char msg[16]="ABCDEFGH"; // exactly 8 bytes
    int out_len; pad(msg,8,8,&out_len);
    printf("out_len=%d (must be 16 for unambiguous unpadding)\n",out_len);
    return 0;
}