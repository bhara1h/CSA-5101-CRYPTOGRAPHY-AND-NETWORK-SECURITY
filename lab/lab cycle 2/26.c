#include <stdio.h>
int main(){
    printf("Unsafe to reuse n after leaking d\n");
    printf("e1*d1 -1 = k*phi(n), attacker can factor n using this multiple of phi\n");
    printf("Must generate new p,q and new n\n");
    return 0;
}