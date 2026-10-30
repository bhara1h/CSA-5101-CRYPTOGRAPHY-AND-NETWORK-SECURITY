#include <stdio.h>
#define TOTAL_LANES 25
#define RATE_LANES 16
#define CAPACITY_LANES 9
int main(void) {
    int state[TOTAL_LANES] = {0};
    int block[RATE_LANES];
    int i, allNonzero = 0;
    printf("SHA-3 State Analysis\n");
    printf("Total lanes    : %d\n", TOTAL_LANES);
    printf("Rate lanes     : %d\n", RATE_LANES);
    printf("Capacity lanes : %d\n\n", CAPACITY_LANES);
    for (i = 0; i < RATE_LANES; i++) {
        block[i] = 1;
    }
    for (i = 0; i < RATE_LANES; i++) {
        state[i] ^= block[i];
    }
    printf("After processing the first message block:\n");
    for (i = 0; i < TOTAL_LANES; i++) {
        printf("Lane %2d: %s\n",
               i, state[i] ? "Nonzero" : "Zero");
    }
    for (i = RATE_LANES; i < TOTAL_LANES; i++) {
        if (state[i] == 0) {
            allNonzero = 0;
            break;
        }
        allNonzero = 1;
    }
    if (allNonzero) {
        printf("\nAll capacity lanes are nonzero.\n");
    } else {
        printf("\nCapacity lanes remain zero.\n");
        printf("Without the permutation, they never become nonzero.\n");
    }
    return 0;
}
