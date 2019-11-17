#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int a=0,x=0;
    int i=0;
    scanf("%u",&a);
    x=a;
    for(;i<32;i++)
    {
        printf("%i",(x>>31)&1);
        x<<=1;
    }
    printf("\n");
    x=a;
    i=0;
    while(((x>>31)&1)==0&i<31)
    {
        i++;
        x<<=1;
    };
    for(;i<32;i++)
    {
        printf("%i",(x>>31)&1);
        x<<=1;
    }
    return 0;
}
