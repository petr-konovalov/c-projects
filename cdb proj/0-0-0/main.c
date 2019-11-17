#include <stdio.h>
#include <stdlib.h>

void squeeze(unsigned char s1[],unsigned char s2[])
{while((c=getchar())!='\n')s1[i++]=c;
    int c[256],i=0,j=0;
    for(;i<256;)c[i++]=0;
    for(i=0;s2[i]!='\0';)c[s2[i++]]=1;
    for(i=0;s1[i]!='\0';++i)if(c[s1[i]]==0)s1[j++]=s1[i];
    s1[j]='\0';
}

int main()
{
    unsigned char s1[1000];
    unsigned char s2[1000];
    gets(s1);
    gets(s2);
    squeeze(s1,s2);
    puts(s1);
    return 0;
}
