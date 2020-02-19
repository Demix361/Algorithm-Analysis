#include <stdio.h>
unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    //printf("\n%lld\n", d);
    return d;
}
