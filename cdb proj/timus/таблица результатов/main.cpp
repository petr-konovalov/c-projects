#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

int main()
{
    queue<int> commands[101];
    int n = 0;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int id, M;
        scanf("%i %i", &id, &M);
        commands[M].push(id);
    }

    for (int i = 100; i >= 0; --i)
    {
        while (!commands[i].empty())
        {
            printf("%i %i\n", commands[i].front(), i);
            commands[i].pop();
        }
    }
    return 0;
}
