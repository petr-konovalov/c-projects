#include <iostream>
#include "logicalTree.h"
#define MAX_EXPRESSION_SIZE 1024

using namespace std;

int main()
{
    char input[MAX_EXPRESSION_SIZE];

    cin >> input;
    Tree *tree = createTree(input);
    showTree(tree);

    cout << "result: ";
    if (getResultTree(tree))
        cout << '1' << endl;
    else
        cout << '0' << endl;

    return 0;
}
