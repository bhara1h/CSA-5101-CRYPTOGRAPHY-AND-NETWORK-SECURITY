#include <stdio.h>
long long gcd(long long a, long long b)
{
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
long long modInverse(long long e, long long phi)
{
    long long t = 0, newT = 1;
    long long r = phi, newR = e;
    while (newR != 0) {
        long long q = r / newR;
        long long temp = t - q * newT;
        t = newT;
        newT = temp;
        temp = r - q * newR;
        r = newR;
        newR = temp;
    }
    if (r != 1)
        return -1;
    t %= phi;
    if (t < 0)
        t += phi;
    return t;
}

int main(void)
{
    long long n, e, m;
    long long factor, p, q, phi, d;
    printf("Enter RSA modulus n: ");
    scanf("%lld", &n);
    printf("Enter public exponent e: ");
    scanf("%lld", &e);
    printf("Enter plaintext block m: ");
    scanf("%lld", &m);
    factor = gcd(m, n);
    printf("\nGCD(m, n) = %lld\n", factor);
    if (factor == 1) {
        printf("No non-trivial common factor found.\n");
        printf("This plaintext block does not reveal a factor of n.\n");
        return 0;
    }
    if (factor == n) {
        printf("The block equals 0 modulo n or shares all of n.\n");
        printf("It does not identify a unique prime factor.\n");
        return 0;
    }

    p = factor;
    q = n / p;

    if (p * q != n) {
        printf("Invalid factorization.\n");
        return 1;
    }

    phi = (p - 1) * (q - 1);
    d = modInverse(e, phi);

    printf("Factor p = %lld\n", p);
    printf("Factor q = %lld\n", q);
    printf("phi(n) = %lld\n", phi);

    if (d == -1) {
        printf("Private exponent does not exist for this e.\n");
        return 1;
    }

    printf("Private exponent d = %lld\n", d);
    printf("Private key = (%lld, %lld)\n", d, n);

    return 0;
}
