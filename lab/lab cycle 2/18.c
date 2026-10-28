#include <stdio.h>
int PC2[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
int main(){
    for(int i=0;i<48;i++){
        if(i<24 && PC2[i]>28) {printf("fail\n"); return 0;}
        if(i>=24 && PC2[i]<=28) {printf("fail\n"); return 0;}
    }
    printf("First 24 from C(1-28), Second 24 from D(29-56) - disjoint\n");
    return 0;
}