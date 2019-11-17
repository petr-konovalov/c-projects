#include <stdio.h>
#include <stdlib.h>
#define N 100

struct matrix
{
    int elements[N][N];         //массив элементов матрицы (с запасом)
    size_t n;                   //высота матрицы
    size_t m;                   //ширина матрицы
};

void swap(int *a, int *b)
{
    int c = *b;
    *b = *a;
    *a = c;
}

int *getmatrixelement(const struct matrix *matr, const size_t i, const size_t j)
{
    if (0 < i && i < matr->n && 0 < j && j < matr->m)
        return &matr->elements[i][j];
    else
        return NULL;
}

int getmatrix(struct matrix *matr, const size_t n, const size_t m)
{
    if (!(0 < m && m < N && 0 < n && n < N))
        return 0;
    else
    {
        int i = 0;
        int j = 0;
        for (i = 0; i < n; ++i)
            for (j = 0; j < m; ++j)
                scanf("%i", &matr->elements[i][j]);
        matr->m = m;
        matr->n = n;
        return 1;
    }
}

void putmatrix(struct matrix *matr)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < matr->n; ++i)
    {
        for (j = 0; j < matr->m; ++j)
            printf("%4i ", matr->elements[i][j]);
        printf("\n");
    }
}

int addmatrix(struct matrix *firstmatr, const struct matrix *secondmatr)
{
    if (!(firstmatr->n == secondmatr->n && firstmatr->m == secondmatr->m))
        return 0;
    else
    {
        int i = 0;
        int j = 0;
        for (i = 0; i < firstmatr->n; ++i)
            for (j = 0; j < firstmatr->m; ++j)
                firstmatr->elements[i][j] += secondmatr->elements[i][j];
        return 1;
    }
}

void multmatrixnumb(struct matrix *matr, const int number)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < matr->n; ++i)
        for (j = 0; j < matr->m; ++j)
            matr->elements[i][j] *= number;
}

int multmatrix(struct matrix *firstmatr, const struct matrix *secondmatr)
{
    if (!(firstmatr->m == secondmatr->n))
        return 0;
    else
    {
        struct matrix buffer;
        int i = 0;
        int j = 0;
        int l = 0;
        buffer.n = firstmatr->n;
        buffer.m = secondmatr->m;
        for (i = 0; i < firstmatr->n; ++i)
            for (j = 0; j < secondmatr->m; ++j)
            {
                buffer.elements[i][j] = 0;
                for (l = 0; l < firstmatr->m; ++l)
                    buffer.elements[i][j] += firstmatr->elements[i][l]*secondmatr->elements[l][j];
            }
        *firstmatr = buffer;
        return 1;
    }
}

int transsquarematrix(struct matrix *matr)
{
    if (!(matr->n == matr->m))
        return 0;
    else
    {
        int i = 0;
        int j = 0;
        for (i = 0; i < matr->n; ++i)
            for (j = i + 1; j < matr->m; ++j)
                swap(&matr->elements[i][j], &matr->elements[j][i]);
        return 1;
    }
}

int main()
{
    struct matrix buffer;
    struct matrix matr1;
    struct matrix matr2;
    int n1, m1, n2, m2;
    int i, j;

    scanf("%i %i %i %i", &n1, &m1, &n2, &m2);

    getmatrix(&matr1, n1, m1);
    getmatrix(&matr2, n2, m2);
    putmatrix(&matr1);
    printf("\n");
    putmatrix(&matr2);
    printf("\n");

    buffer = matr1;

    if (addmatrix(&matr1, &matr2))
        putmatrix(&matr1);
    else
        printf("CAN NOT BE ADDED\n");
    printf("\n");

    matr1 = buffer;

    if (multmatrix(&matr1, &matr2))
        putmatrix(&matr1);
    else
        printf("CAN NOT BE MULTIPLICATED\n");
    printf("\n");

    matr1 = buffer;

    int number;

    scanf("%i", &number);
    multmatrixnumb(&matr1, number);
    putmatrix(&matr1);
    printf("\n");

    matr1 = buffer;

    if (transsquarematrix(&matr1))
        putmatrix(&matr1);
    else
        printf("CAN NOT BE TRANSPOSED\n");
    printf("\n");

    matr1 = buffer;

    scanf("%i %i", &i, &j);

    printf("%i", *getmatrixelement(&matr1, i, j));

    return 0;
}
