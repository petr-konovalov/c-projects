#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

bool rC(int value)
{
    return value & 1;
}

int generator()
{
    return rand() % 16;
}

void printer(int value)
{
    printf("%i ", value);
}

int main()
{
    vector<int> a;
    a.resize(8);
    generate(a.begin(), a.end(), &generator);
    for_each(a.begin(), a.end(), &printer);
    printf("\n");
    partition(a.begin(), a.end(), &rC);
    for_each(a.begin(), a.end(), &printer);
    return 0;
}
