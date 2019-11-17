#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
	Stack *stack = createStack();

	push(stack, 1);
	push(stack, 2);
	push(stack, 3);

	cout << pop(stack) << endl;
	cout << pop(stack) << endl;
	cout << pop(stack) << endl;
	cout << pop(stack) << endl;
	
	//stack->

	int x = 0;
	cin >> x;
	return 0;
}