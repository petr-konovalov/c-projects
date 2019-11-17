#include "logicalTree.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

struct Tree
{
    char value;
    Tree *left;
    Tree *right;
};

Tree *atom(char **input);
Tree *form(char **input);
Tree *term(char **input);

bool isBool(char input)
{
    return input == '1' || input == '0';
}

char **getNext(char **input)
{
    return &(++*input);
}

Tree *atom(char **input)
{
    if (**input == '(')
    {
        Tree *newForm = form(getNext(input));
        getNext(input);
        return newForm;
    }

    Tree *newAtom = new Tree;
    newAtom->value = **input;

    if (isBool(**input))
    {
        newAtom->left = NULL;
        newAtom->right = NULL;
        getNext(input);
    }
    else if (**input == '!')
    {
        newAtom->right = NULL;
        newAtom->left = atom(getNext(input));
    }

    return newAtom;
}

Tree *form(char **input)
{
    Tree *newTerm = term(input);

    if (**input == '+')
    {
        Tree *newForm = new Tree;

        newForm->value = '+';
        newForm->left = newTerm;
        newForm->right = form(getNext(input));

        return newForm;
    }

    return newTerm;
}

Tree *term(char **input)
{
    Tree *newAtom = atom(input);

    if (**input == '*')
    {
        Tree *newTerm = new Tree;

        newTerm->value = '*';
        newTerm->left = newAtom;
        newTerm->right = term(getNext(input));

        return newTerm;
    }

    return newAtom;
}

bool executeOperation(char operation, bool firstOperand, bool secondOperand)
{
    switch (operation)
    {
        case '0':
            return false;
        case '1':
            return true;
        case '!':
            return !firstOperand;
        case '+':
            return firstOperand || secondOperand;
        case '*':
            return firstOperand && secondOperand;
        default:
            return true;
    }
}

bool getResultTree(const Tree *tree)
{
    if (tree)
    {
        bool firstOperand = getResultTree(tree->left);

        if (firstOperand && tree->value == '+')
            return true;

        if (!firstOperand && tree->value == '*')
            return false;

        bool secondOperand = getResultTree(tree->right);

        return executeOperation(tree->value, firstOperand, secondOperand);
    }

    return true;
}

Tree *createTree(char *logicalExpression)
{
    return form(&logicalExpression);
}

void show(const Tree *tree, int depth)
{
    if (tree)
    {
        show(tree->right, depth + 1);
        cout << setw(depth * 3) << tree->value << endl;
        show(tree->left, depth + 1);
    }
}

void showTree(const Tree *tree)
{
    show(tree, 0);
}
