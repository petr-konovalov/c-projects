#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "expression.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Expression *exp;

    createExpression(&exp);

    printf("Введите выражение:\n");
    char c = 'a';
    while (c != '=')
    {
        c = getchar();
        addExpressionChar(exp, c);
    }

    printf("Результат: %s\n", getExpressionResult(exp));
    printf("Постфиксная форма: %s\n", getExpressionPostfixForm(exp));

    destroyExpression(&exp);
    return 0;
}
