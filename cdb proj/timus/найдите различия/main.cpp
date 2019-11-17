#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

void rotateA(int cube[6])
{
    int temp = cube[0];
    cube[0] = cube[2];
    cube[2] = cube[1];
    cube[1] = cube[4];
    cube[4] = temp;
}

void rotateB(int cube[6])
{
    int temp = cube[5];
    cube[5] = cube[4];
    cube[4] = cube[3];
    cube[3] = cube[2];
    cube[2] = temp;
}

void rotateC(int cube[6])
{
    int temp = cube[5];
    cube[5] = cube[1];
    cube[1] = cube[3];
    cube[3] = cube[0];
    cube[0] = temp;
}

void normalize(int cube[6])
{
    if (cube[0] == 1 || cube[1] == 1 || cube[4] == 0)
        while (cube[2] != 1)
            rotateA(cube);
    else
        while (cube[2] != 1)
            rotateB(cube);
    if (cube[4] == 2)
        while (cube[0] != 3)
            rotateC(cube);
    else
        while (cube[0] != 2)
            rotateC(cube);
}

bool compCube(int c1[6], int c2[6])
{
    return c1[0] == c2[0] && c1[1] == c2[1] &&
           c1[2] == c2[2] && c1[3] == c2[3] &&
           c1[4] == c2[4] && c1[5] == c2[5];
}

struct equalClass
{
    int lider[6];
    vector<int> members;
};

vector<equalClass> res;

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        int cube[6];
        for (int j = 0; j < 6; ++j)
            scanf("%i", cube + j);
        normalize(cube);
        bool b = true;
        for (int j = 0; j < res.size(); ++j)
            if (compCube(res[j].lider, cube))
            {
                b = false;
                res[j].members.push_back(i + 1);
                break;
            }
        if (b)
        {
            equalClass newClass;
            for (int j = 0; j < 6; ++j)
                newClass.lider[j] = cube[j];
            newClass.members.push_back(i + 1);
            res.push_back(newClass);
        }
    }
    printf("%i\n", res.size());
    for (int i = 0; i < res.size(); ++i)
    {
        for (int j = 0; j < res[i].members.size(); ++j)
            printf("%i ", res[i].members[j]);
        printf("\n");
    }
    return 0;
}
