#include <iostream>
#include <stdio.h>

using namespace std;

char game[1000001];

int checkGame(int l, int r, char cGamer)
{
    char c = game[l];
    bool gameEnd = true;
    for (int i = l + 1; i <= r && gameEnd; ++i)
        gameEnd = gameEnd && game[i] == c;
    if (gameEnd)
        return c == cGamer ? 1 : -1;
    if (((r - l + 1) >> 1) & 1)
        return 0;
    int mid = (l + r) / 2;
    char nextGamer = cGamer == 'A' ? 'B' : 'A';
    int resl = checkGame(l, mid, nextGamer);
    if (resl == -1)
        return 1;
    int resr = checkGame(mid + 1, r, nextGamer);
    if (resr == -1)
        return 1;
    if (resl == 0 || resr == 0)
        return 0;
    return -1;
}

int main()
{
    int n;
    scanf("%i", &n);
    scanf("%s", game);
    scanf("%s", game + n);
    int res = checkGame(0, 2 * n - 1, 'A');
    if (res == 1)
        printf("Alice");
    else if (res == -1)
        printf("Bob");
    else
        printf("Draw");
    return 0;
}
