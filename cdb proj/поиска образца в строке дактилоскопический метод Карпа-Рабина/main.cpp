#include <iostream>

using namespace std;

int getCode(char Symbol)
{
    if (Symbol >='a' && Symbol <='z')
        return Symbol - 'a';
    else
        return Symbol - 'A' + 27;
}

bool cmp(char *first, char *second, int length)
{
    bool result = true;
    for(int i = 0; i < length; ++i)
        if (first[i] != second[i])
        {
            result = false;
            break;
        }
    return result;
}

int main()
{
    const int MAX_STRING_LENGTH = 120000;
    const int SIZE = 52;
    char S[MAX_STRING_LENGTH] = "";
    char T[MAX_STRING_LENGTH] = "";
    int hS = 0;
    int hT = 0;
    int lenT = 0;
    int r = 1;
    cin >> S;
    cin >> T;
    while (T[lenT] != '\0')
        ++lenT;
    for (int i = lenT - 1; i >= 0; --i)
    {
         hT += getCode(T[i]) * r;
         hS += getCode(S[i]) * r;
         if (S[i] == '\0')
            return 0;
        if (i > 0)
            r *= SIZE;
    }
    if (hS == hT && cmp(T, S, lenT))
        cout << "0 ";
    for (int i = 0; S[i + lenT] != '\0'; ++i)
    {
        hS = (hS - getCode(S[i]) * r) * SIZE + getCode(S[i + lenT]);
        if (hS == hT && cmp(T, &S[i + 1], lenT))
            cout << i + 1 << ' ';
    }
    return 0;
}
