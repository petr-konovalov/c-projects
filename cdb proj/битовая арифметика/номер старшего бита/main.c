#include <stdio.h>
#include <stdlib.h>

void writebits(unsigned int x,unsigned int b)
{
    if(b>1)writebits(x>>1,b-1);
    printf("%i",x&1);
}

int main()
{
    unsigned int x,b=-1;
    scanf("%u",&x);
    writebits(x,32);
    while(x>0)
    {
        x>>=1;
        b++;
    }
    printf("\n%u",b);
    return 0;
}
