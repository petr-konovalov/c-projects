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

    double a[n][2*n], s[n][n];
    int b[n];

    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {
            scanf("%lf",&a[i][j]);
            s[i][j] = a[i][j];
        }
        b[i]=i;
    }

    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
            a[i][j+n]=(int)(i==j);
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
                for(l=0;l<2*n;++l)
                    a[b[j]][l]+=tmp*a[b[i]][l];
            }
        }
    }

    for (i = 0; i < n; ++i)
    {
        double tmp = a[i][i];
        for (j = i; j < 2 * n; ++j)
            a[i][j] /= tmp;
    }

    for (i = 0; i < n; ++i)
    {
        for (j = i - 1; j >= 0; --j)
        {
            double tmp = -a[j][i];
            if (fabs(tmp) > eps)
                for (l = i; l < 2 * n; ++l)
                    a[j][l] += a[i][l]*tmp;
        }
    }

    for (i=0; i < n; ++i)
    {
        for (j=n; j < 2 * n; ++j)
            printf("%10.3lf", a[b[i]][j]);
        printf("\n");
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            double c = 0;
            for (l = 0; l < n; ++l)
                c += s[i][l] * a[b[l]][j + n];
            printf("%10.3lf", c);
        }
        printf("\n");
    }

    return 0;
}
