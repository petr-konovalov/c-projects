#include "floatStack.h"
#include <stdio.h>

typedef struct FloatNode
{
    float value;
    struct FloatNode *next;
} FloatStack;

void createFloatStack(FloatStack **floats)
{
    *floats = NULL;
}

int isEmptyFloat(const FloatStack *floats)
{
    return floats == NULL;
}

void pushFloat(FloatStack **floats, const float value)
{
    FloatStack *newElement = malloc(sizeof(FloatStack));
    newElement->value = value;
    newElement->next = *floats;
    *floats = newElement;
}

float popFloat(FloatStack **floats)
{
    float value = (*floats)->value;
    FloatStack *temp = *floats;
    *floats = (*floats)->next;
    free(temp);
    return value;
}

float topFloat(const FloatStack *floats)
{
    return floats->value;
}

void destroyFloatStack(FloatStack **floats)
{
    while (*floats)
    {
        FloatStack *next = (*floats)->next;
        free(*floats);
        *floats = next;
    }
}
