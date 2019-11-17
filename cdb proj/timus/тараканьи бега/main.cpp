#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

struct element
{
    double x;
    double y;
};

struct Node
{
    element value;
    Node *next;
};

struct List
{
    Node *head;
    Node *tail;
};

void addList(List &l, double x, double y)
{
    if (!l.head)
    {
        l.head = new Node;
        l.tail = l.head;
        l.head->value.x = x;
        l.head->value.y = y;
    }
    else
    {
        l.tail->next = new Node;
        l.tail->next->value.x = x;
        l.tail->next->value.y = y;
        l.tail = l.tail->next;
    }
}

int main()
{
    int m;
    scanf("%i", &m);
    double tx[m], ty[m];
    double left = 10000, right = -10000, top = -10000, bottom = 10000;

    for (int i = 0; i < m; ++i)
    {
        scanf("%lf %lf", &tx[i], &ty[i]);
        if (tx[i] < left)
            left = tx[i];
        if (tx[i] > right)
            right = tx[i];
        if (ty[i] < bottom)
            bottom = ty[i];
        if (ty[i] > top)
            top = ty[i];
    }

    int tHor = ceil(sqrt(top - bottom)) + 1;
    int tVer = ceil(sqrt(right - left)) + 1;

    List table[tHor][tVer];

    for (int i = 0; i < m; ++i)
        addList(table[(int)(ty[i] / tHor)][(int)(tx[i] / tVer)], tx[i], ty[i]);

    return 0;
}
