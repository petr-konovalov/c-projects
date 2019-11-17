#include <iostream>
#include <stdio.h>
#include <queue>
#include <map>

using namespace std;

map<int, map<int, int> > pState;

bool checkState(int a, int b)
{
    return !(pState.find(a) == pState.end() || pState[a].find(b) == pState[a].end());
}

queue<pair<int, int> > q;

void handleState(int na, int nb, int t, int op)
{
    if (!checkState(na, nb))
    {
        pState[na][nb] = t + op;
        q.push(make_pair(na, nb));
    }
}

int bfs(int A, int B, int N)
{
    handleState(0, 0, 0, 0);
    for (int i = 0; i <= 100000 && !q.empty(); ++i)
    {
        int ca = q.front().first, cb = q.front().second;
        q.pop();
        int t = (10001 * ca + cb) * 10;
        if (ca == N || cb == N)
            return ca * 10001 + cb;
        int na, nb;
        na = A; nb = cb;
        handleState(na, nb, t, 0);
        na = ca; nb = B;
        handleState(na, nb, t, 1);
        na = 0; nb = cb;
        handleState(na, nb, t, 2);
        na = ca; nb = 0;
        handleState(na, nb, t, 3);
        nb = min(B, ca + cb); na = ca - (nb - cb);
        handleState(na, nb, t, 4);
        na = min(A, ca + cb); nb = cb - (na - ca);
        handleState(na, nb, t, 5);
    }
    return -1;
}

void printAns(int a, int b)
{
    int cstate = pState[a][b];
    int t = cstate / 10, op = cstate % 10;
    int na = t / 10001, nb = t % 10001;
    if (na != 0 || nb != 0)
        printAns(na, nb);
    switch(op)
    {
        case 0:
            printf(">A\n");
            break;
        case 1:
            printf(">B\n");
            break;
        case 2:
            printf("A>\n");
            break;
        case 3:
            printf("B>\n");
            break;
        case 4:
            printf("A>B\n");
            break;
        case 5:
            printf("B>A\n");
            break;
    }
}

int main()
{
    int A, B, N;
    cin >> A >> B >> N;
    int state = bfs(A, B, N);
    if (state == -1)
        printf("Impossible\n");
    else
        printAns(state / 10001, state % 10001);
    return 0;
}
