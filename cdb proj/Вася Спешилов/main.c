#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "rus");
    int k = 0;
    scanf("%i", &k);
    printf("��� %i ", k);
    switch(k / 10)
    {
    case 1:
        printf("���");
    break;
    default:
        switch(k % 10)
        {
        case 1:
            printf("���");
        break;
        case 2:
        case 3:
        case 4:
            printf("����");
        break;
        default:
            printf("���");
        }
    }
    return 0;
}
