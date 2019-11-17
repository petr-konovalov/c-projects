#ifndef LOGICALTREE_H_INCLUDED
#define LOGICALTREE_H_INCLUDED

struct Tree;

Tree *createTree(char *logicalExpression);
bool getResultTree(const Tree *tree);
void showTree(const Tree *tree);

#endif // LOGICALTREE_H_INCLUDED
