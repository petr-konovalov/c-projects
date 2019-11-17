#include <stdio.h>
#include <stdlib.h>

void writebits(unsigned int x,unsigned int b)
{
    if(b>1)writebits(x>>1,b-1);
    printf("%i",x&1);
}

int main()
{
    unsigned int x,i;
    scanf("%u %u",&x,&i);
    writebits(x,32);
    printf("\n");
    x=x>>i<<i-1|~(~0<<i)&x;
    writebits(x,32);
    return 0;
}
