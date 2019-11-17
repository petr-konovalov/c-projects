#ifndef CHARSTACK_H_INCLUDED
#define CHARSTACK_H_INCLUDED

typedef struct CharNode CharStack;

void createCharStack(CharStack **chars);

int isEmptyChar(const CharStack *chars);

void pushChar(CharStack **chars, const char value);

char popChar(CharStack **chars);

char topChar(const CharStack *chars);

void destroyCharStack(CharStack **chars);

#endif // CHARSTACK_H_INCLUDED
