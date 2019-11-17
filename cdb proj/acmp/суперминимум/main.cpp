#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;

deque<int> mins;

void add(int value)
{
    while (!mins.empty() && mins.back() > value)
        mins.pop_back();
    mins.push_back(value);
}

int getMin()
{
    return mins.front();
}

void remove(int element)
{
    if (!mins.empty() && mins.front() == element)
        mins.pop_front();
}

int main()
{
    deque<int> curr;
    int n, k, t;
    scanf("%i %i", &n, &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%i", &t);
        add(t);
        curr.push_back(t);
    }
    for (int i = 0; i < n - k; ++i)
    {
        printf("%i ", getMin());
        remove(curr.front());
        scanf("%i", &t);
        add(t);
        curr.push_back(t);
        curr.pop_front();
    }
    printf("%i", getMin());
    return 0;
}
