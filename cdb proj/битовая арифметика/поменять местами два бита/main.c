#include <stdio.h>
#include <stdlib.h>

void writebits(unsigned int x,unsigned int b)
{
    if(b>1)writebits(x>>1,b-1);
    printf("%i",x&1);
}

int main()
{
    unsigned int x,a,b;
    scanf("%u %u %u",&x,&a,&b);
    writebits(x,32);
    printf("\n");
    x=x&~(1<<a|1<<b)|(x>>a&1)<<b|(x>>b&1)<<a;
    printf("%i\n",x);
    writebits(x,32);
    return 0;
}
