#include "Stack.h"

struct StackElement
{
	int data;
	StackElement *next;
};

struct Stack
{
	StackElement *top;
	int size;
};

Stack* createStack()
{
	Stack *s = new Stack;
	s->top = nullptr;
	s->size = 0;
	return s;
}

void push(Stack *s, int value)
{
	StackElement *newElement = new StackElement;
	newElement->data = value;
	newElement->next = s->top;
	s->top = newElement;
	s->size++;
}

int pop(Stack *s)
{
	if (isEmpty(s))
		return -1;

	int x = s->top->data;
	StackElement *toDelete = s->top;
	s->top = s->top->next;
	delete toDelete;
	s->size--;
	return x;
}

bool isEmpty(Stack const *s)
{
	return s->size == 0;
}