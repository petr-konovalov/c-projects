#ifndef FLOATSTACK_H_INCLUDED
#define FLOATSTACK_H_INCLUDED

typedef struct FloatNode FloatStack;

void createFloatStack(FloatStack **floats);

int isEmptyFloat(const FloatStack *floats);

void pushFloat(FloatStack **floats, const float value);

float popFloat(FloatStack **floats);

float topFloat(const FloatStack *floats);

void destroyFloatStack(FloatStack **floats);

#endif // FLOATSTACK_H_INCLUDED
