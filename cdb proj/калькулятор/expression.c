#include "expression.h"
#include "charStack.h"
#include "floatStack.h"
#include "stdlib.h"
#include "math.h"
#define EXPRESSION_LENGTH 1024
#define BUFFER_LENGTH 32

typedef struct ExpressionStruct
{
    FloatStack *numbers;
    CharStack *operations;
    char postfixEntry[EXPRESSION_LENGTH + 1];
    char buffer[BUFFER_LENGTH + 1];
    int bufferLength;
    int state;
    int wrong;
    int length;
} Expression;

const char *getExpressionResult(Expression *exp)
{
    if (exp->wrong)
        return "Îøèáêà";
    else
    {
        snprintf(exp->buffer, BUFFER_LENGTH, "%f", topFloat(exp->numbers));
        return exp->buffer;
    }
}

void createExpression(Expression **exp)
{
    *exp = malloc(sizeof(Expression));
    createFloatStack(&(*exp)->numbers);
    createCharStack(&(*exp)->operations);
    (*exp)->length = 0;
    (*exp)->wrong = 0;
    (*exp)->state = 0;
    (*exp)->bufferLength = 0;
}

int getPriority(const char c)
{
    switch (c)
    {
        case '=':
            return 0;
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
        default:
            return -1;
    }
}

float executeOperation(const char operation,
                       const float firstOperand, const float secondOperand)
{
    switch (operation)
    {
        case '+':
            return firstOperand + secondOperand;
        case '-':
            return firstOperand - secondOperand;
        case '*':
            return firstOperand * secondOperand;
        case '/':
            return firstOperand / secondOperand;
        case '^':
            return pow(firstOperand, secondOperand);
        default:
            return 0.0f;
    }
}

int checkOperation(const char operation,
                   const float firstOperand, const float secondOperand)
{
    switch (operation)
    {
        case '/':
            if (secondOperand == 0)
                return 0;
        case '^':
            if (firstOperand == 0 && secondOperand <= 0 || firstOperand < 0)
                return 0;
    }
    return 1;
}

void addExpressionEntryChar(Expression *exp, const char c)
{
    snprintf(&exp->postfixEntry[exp->length], EXPRESSION_LENGTH - exp->length, "%c%c", c, ' ');
    exp->length += 2;
}

int isDigit(const char c)
{
    return '0' <= c && c <='9';
}

int isExponent(const char c)
{
    return c == 'e' || c =='E';
}

int isSign(const char c)
{
    return c == '+' || c == '-' || c =='*' || c=='/' || c=='^' || c=='=';
}

int isPoint(const char c)
{
    return c=='.';
}

void flushExpressionBuffer(Expression *exp)
{
    exp->buffer[exp->bufferLength] = '\0';
    pushFloat(&exp->numbers, atof(exp->buffer));
    snprintf(&exp->postfixEntry[exp->length], EXPRESSION_LENGTH - exp->length, "%s%s", exp->buffer, " ");
    exp->length += exp->bufferLength + 1;
    exp->bufferLength = 0;
}

void pushBuffer(Expression *exp, const char c)
{
    exp->buffer[exp->bufferLength++] = c;
}

void parseStateZero(Expression *exp, const char c)
{
    if (isDigit(c))
    {
        pushBuffer(exp, c);
        exp->state = 1;
    }
    else if (c == '(')
        exp->state = 2;
}

void parseStateOne(Expression *exp, const char c)
{
    if (isDigit(c) || isPoint(c))
        pushBuffer(exp, c);
    else if (isExponent(c))
    {
        pushBuffer(exp, c);
        exp->state = 3;
    }
    else if (isSign(c))
    {
        flushExpressionBuffer(exp);
        exp->state = 0;
    }
    else if (c == ')')
    {
        flushExpressionBuffer(exp);
        exp->state = 5;
    }
}

void parseStateTwo(Expression *exp, const char c)
{
    if (isDigit(c))
    {
        pushBuffer(exp, c);
        exp->state = 1;
    }
    else if (isSign(c))
    {
        exp->bufferLength = 1;
        exp->buffer[0] = '0';
        flushExpressionBuffer(exp);
        exp->state = 0;
    }
}

void parseStateThree(Expression *exp, const char c)
{
    if (isSign(c))
    {
        pushBuffer(exp, c);
        exp->state = 4;
    }
}

void parseStateFour(Expression *exp, const char c)
{
    if (isDigit(c))
        pushBuffer(exp, c);
    else if (isSign(c))
    {
        flushExpressionBuffer(exp);
        exp->state = 0;
    }
    else if (c == ')')
    {
        flushExpressionBuffer(exp);
        exp->state = 5;
    }
}

void parseStateFive(Expression *exp, const char c)
{
    if (isSign(c))
        exp->state = 0;
}

void parseExpression(Expression *exp, const char c)
{
    switch (exp->state)
    {
        case 0:
            parseStateZero(exp, c);
            break;
        case 1:
            parseStateOne(exp, c);
            break;
        case 2:
            parseStateTwo(exp, c);
            break;
        case 3:
            parseStateThree(exp, c);
            break;
        case 4:
            parseStateFour(exp, c);
            break;
        case 5:
            parseStateFive(exp, c);
            break;
    }
}

int executeExpressionTopOperation(Expression *exp)
{
    float secondOperand = popFloat(&exp->numbers);
    float firstOperand = popFloat(&exp->numbers);
    if (!checkOperation(topChar(exp->operations), firstOperand, secondOperand))
        return 0;
    pushFloat(&exp->numbers,
              executeOperation(topChar(exp->operations), firstOperand, secondOperand));
    addExpressionEntryChar(exp, popChar(&exp->operations));
    return 1;
}

int addExpressionOperation(Expression *exp, const char c)
{
    int priority = getPriority(c);
    if (c != '(')
        while (!isEmptyChar(exp->operations) && priority <= getPriority(topChar(exp->operations)))
            if (!executeExpressionTopOperation(exp))
                return 0;
    pushChar(&exp->operations, c);
    return 1;
}

void addExpressionChar(Expression *exp, const char c)
{
    if (!exp->wrong)
    {
        parseExpression(exp, c);
        if (exp->state != 4)
        {
            if (getPriority(c) != -1)
            {
                if (!addExpressionOperation(exp, c))
                    exp->wrong = 1;
            }
            else if (c == ')')
            {
                while (topChar(exp->operations) != '(')
                    if (!executeExpressionTopOperation(exp))
                        exp->wrong = 1;
                popChar(&exp->operations);
            }
        }
    }
}

const char *getExpressionPostfixForm(const Expression *exp)
{
    return exp->postfixEntry;
}

void destroyExpression(Expression **exp)
{
    destroyCharStack(&(*exp)->operations);
    destroyFloatStack(&(*exp)->numbers);
    free(*exp);
    *exp = NULL;
}
