#include <iostream>
#include <stdio.h>
#include <deque>
#include <queue>

using namespace std;

struct item
{
    int value;
    int pos;
};

void addItem(deque<item> &buf, int pos, int value)
{
    while(!buf.empty() && buf.front().value <= value)
        buf.pop_front();
    item e;
    e.pos = pos;
    e.value = value;
    buf.push_front(e);
}

int getItem(deque<item> &buf, int pos, int M)
{
    while (pos - buf.back().pos >= M)
        buf.pop_back();

    return buf.back().value;
}

int main()
{
    deque<item> buf;
    queue<int> out;
    int m;

    scanf("%i", &m);

    int in = 0;
    int pos = 0;
    for (pos = 0; pos < m - 1; ++pos)
    {
        scanf("%i", &in);
        addItem(buf, pos, in);
    }
    scanf("%i", &in);
    while (in != -1)
    {
        addItem(buf, pos, in);
        out.push(getItem(buf, pos, m));
        ++pos;
        scanf("%i", &in);
    }

    while (!out.empty())
    {
        printf("%i\n", out.front());
        out.pop();
    }
    return 0;
}
