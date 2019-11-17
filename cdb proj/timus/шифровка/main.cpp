#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;

int main()
{
    deque<char> chars;
    char c;

    while ((c = getchar()) != '\n')
    {
        if (chars.empty() || chars.back() != c)
            chars.push_back(c);
        else
            chars.pop_back();
    }
    while (!chars.empty())
    {
        putchar(chars.front());
        chars.pop_front();
    }
    return 0;
}
