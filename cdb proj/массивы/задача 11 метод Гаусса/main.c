#include <stdio.h>
#include <stdlib.h>
#define eps 1e-10

void swap(int *a,int *b)
{
    int c=*a;
    *a=*b;
    *b=c;
}

int main()
{
    int n=0,i=0,j=0,l=0;
    scanf("%i",&n);

    double a[n][n+1];
    double x[n];
    int b[n];

    for(i=0;i<n;++i)
    {
        for(j=0;j<n+1;++j)
            scanf("%lf",&a[i][j]);
        b[i]=i;
    }

    for(i=0;i<n;++i)
    {
        for(j=i;j<n&&fabs(a[b[j]][i])<eps;++j);
        if(j<n)
        {
            if(j>i)swap(&b[i],&b[j]);
            for(j=i+1;j<n;++j)
            {
                double tmp=-a[b[j]][i]/a[b[i]][i];
                for(l=0;l<n+1;++l)
                    a[b[j]][l]+=tmp*a[b[i]][l];
            }
        }
    }

    for (i=0; i < n; ++i)
    {
        for (j=0; j < n; ++j)
            printf("%15.10lf", a[b[i]][j]);
        printf("\n");
    }

    x[n - 1] = 1;
    for(i=n-2;i>=0;--i)
    {
        double tmp=a[b[i]][n];
        for(j=i+1;j<n;++j)
            tmp-=x[j]*a[b[i]][j];
        x[i]=tmp/a[b[i]][i];
    }

    for(i=0;i<n;++i)
        printf("%15.10lf ",x[i]);
    printf("\n");

    double norma = 0;
    for (i = 0; i < n; ++i)
        norma += x[i] * x[i];
    norma = sqrt(norma);
    for (i = 0; i < n; ++i)
        x[i] /= norma;

    for(i=0;i<n;++i)
        printf("%15.10lf ",x[i]);

    return 0;
}
