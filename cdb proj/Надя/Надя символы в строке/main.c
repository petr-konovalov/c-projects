#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int symbols_count_compare(char *str, char a, char b)
{
    int acount = 0;
    int bcount = 0;

    while (*str)
    {
        if (*str == a)
            ++acount;
        if (*str == b)
            ++bcount;

        ++str;
    }

    return acount > bcount;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const STRING_LENGTH = 1024;

    char a;
    char b;
    char enter_reader;
    char str[STRING_LENGTH];

    printf("Введите строку: ");
    fgets(str, STRING_LENGTH - 1, stdin);
    printf("Введите первый символ: ");
    scanf("%c%c", &a, &enter_reader);
    printf("Введите второй символ: ");
    scanf("%c%c", &b, &enter_reader);

    if (symbols_count_compare(str, a, b))
        printf("Первый символ встречается чаще второго");
    else
        printf("Первый симвод встречается не чаще второго");
    return 0;
}
