#include "charStack.h"
#include <stdio.h>

typedef struct CharNode
{
    char value;
    struct CharNode *next;
} CharStack;

void createCharStack(CharStack **chars)
{
    *chars = NULL;
}

int isEmptyChar(const CharStack *chars)
{
    return chars == NULL;
}

void pushChar(CharStack **chars, const char value)
{
    CharStack *newElement = malloc(sizeof(CharStack));
    newElement->value = value;
    newElement->next = *chars;
    *chars = newElement;
}

char popChar(CharStack **chars)
{
    char value = (*chars)->value;
    CharStack *temp = *chars;
    *chars = (*chars)->next;
    free(temp);
    return value;
}

char topChar(const CharStack *chars)
{
    return chars->value;
}

void destroyCharStack(CharStack **chars)
{
    while (*chars)
    {
        CharStack *next = (*chars)->next;
        free(*chars);
        *chars = next;
    }
}
