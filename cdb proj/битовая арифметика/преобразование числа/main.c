#include <stdio.h>
#include <stdlib.h>

void writebits(unsigned int x,unsigned int b)
{
    if(b>1)writebits(x>>1,b-1);
    printf("%i",x&1);
}

int main()
{
    unsigned int x;
    scanf("%u",&x);
    writebits(x,32);
    printf("\n");
    writebits(x<<1,32);
    printf("\n");
    writebits(x>>1,32);
    printf("\n");
    x=x^x>>1^x<<1;
    writebits(x,32);
    printf("\n%u",x);
    return 0;
}
