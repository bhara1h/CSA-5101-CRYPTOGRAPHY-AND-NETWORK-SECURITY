#include <stdio.h>
int main(){
    int n=3599, e=31;
    int p=0,q=0;
    for(int i=2;i<n;i++) if(n%i==0){p=i; q=n/i; break;}
    int phi=(p-1)*(q-1);
    int d=0;
    for(int i=1;i<phi;i++) if((e*i)%phi==1){d=i; break;}
    printf("p=%d q=%d phi=%d d=%d\n",p,q,phi,d);
    return 0;
}