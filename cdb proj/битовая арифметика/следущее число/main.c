#include <stdio.h>
#include <stdlib.h>

void writebits(unsigned int x,unsigned int b)
{
    if(b>1)writebits(x>>1,b-1);
    printf("%i",x&1);
}

int main()
{
    unsigned int n=0,y=0,i=0;
    scanf("%u",&n);
    y=n&~(n>>1);
    writebits(n,32);printf("\n");
    while((y&1)==0)
    {
        y>>=1;
        i++;
    }
    n=n&~(1<<i)|(1<<i+1);
    y=n&~(~0<<i);
    while((y&1)==0)
    {
        y>>=1;
    }
    n=n&(~0<<i)|y;
    printf("%u\n",n);
    writebits(n,32);
    return 0;
}
