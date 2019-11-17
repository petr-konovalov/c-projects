#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m=0,n=0,i=0,j=0,k=0;
    scanf("%i %i",&m,&n);
    int a[m],b[n],c[m+n];
    for(i=0;i<m;i++)
        scanf("%i",&a[i]);
    for(i=0;i<n;i++)
        scanf("%i",&b[i]);
    i=0;j=0;
    for(k=0;k<m+n;k++)
    {
        if(i<m&&a[i]<b[j]||j==n)
        {
            c[k]=a[i];
            i++;
        }
        else
        {
            c[k]=b[j];
            j++;
        }
    }
    for(i=0;i<k;i++)
        printf("%i ",c[i]);
    return 0;
}
