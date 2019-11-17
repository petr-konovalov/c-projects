#include <stdio.h>
#include <stdlib.h>

void writebits(unsigned int x,unsigned int b)
{
    if(b>1)writebits(x>>1,b-1);
    printf("%i",x&1);
}

int main()
{
    unsigned int x,a,b,c;
    scanf("%u %u %u",&a,&b,&c);
    x=((a&b&c)|~(a^b^c))&(a|b|c);
    printf("%u\n",x);
    writebits(a,32);printf("\n");
    writebits(b,32);printf("\n");
    writebits(c,32);printf("\n");
    writebits(x,32);printf("\n");
    return 0;
}
