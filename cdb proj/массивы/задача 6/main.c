#include <stdio.h>
#include <stdlib.h>

int comps[3],swaps[3],id=0;

void swap(int*,int*);
int comp(int,int);
void quick(int*,int,int);
void bubble(int*,int);
void select(int*,int);

int main()
{
    int n=0;
    int i=0;
    int j=0;

    scanf("%i",&n);
    int a[n],b[n];

    for(i=0;i<n;++i)
    {
        scanf("%i",&b[i]);
        a[i]=b[i];
    }

    quick(a,0,n-1);
    for(i=0;i<n;++i)a[i]=b[i];++id;
    bubble(a,n);
    for(i=0;i<n;++i)a[i]=b[i];++id;
    select(a,n);
    for(i=0;i<3;++i)printf("%5i %5i\n",comps[i],swaps[i]);
    return 0;
}

//----------------------------------------------------------------------------------------

void swap(int *a,int *b)
{
    int c=*a;
    *a=*b;
    *b=c;
    ++swaps[id];
}

int comp(int a,int b)
{
    ++comps[id];
    return a-b;
}

void quick(int *a,int m,int n)
{
    int p=a[(m+n)/2];
    int i=m,j=n;
    while(i<=j)
    {
        while(comp(a[i],p)<0)++i;
        while(comp(a[j],p)>0)--j;
        if(i<=j)
        {
            if(i<j)swap(&a[i],&a[j]);
            ++i;--j;
        }
    }
    if(i<n)quick(a,i,n);
    if(m<j)quick(a,m,j);
}

void bubble(int *a,int n)
{
    int i=0,j=0;
    for(i=n-1;i>=0;--i)
        for(j=0;j<i;j++)
            if(comp(a[j],a[j+1])>0)swap(&a[j],&a[j+1]);
}

void select(int *a,int n)
{
    int i=0,j=0;
    for(i=0;i<n;++i)
        for(j=i;j<n;++j)
            if(comp(a[i],a[j])>0)swap(&a[i],&a[j]);
}
