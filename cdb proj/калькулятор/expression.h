#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

typedef struct ExpressionStruct Expression;

void createExpression(Expression **exp);

const char *getExpressionResult(Expression *exp);

void addExpressionChar(Expression *exp, const char c);

const char *getExpressionPostfixForm(const Expression *exp);

void destroyExpression(Expression **exp);


#endif // EXPRESSION_H_INCLUDED
