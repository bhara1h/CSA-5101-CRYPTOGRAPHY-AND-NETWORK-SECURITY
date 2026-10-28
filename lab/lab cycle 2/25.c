#include <stdio.h>
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main(){
    int n=3599;
    int block=118; // example block sharing factor 59
    int g=gcd(block,n);
    if(g!=1 && g!=n){
        printf("Found factor: %d, other=%d\n",g,n/g);
        printf("RSA broken\n");
    }
    return 0;
}