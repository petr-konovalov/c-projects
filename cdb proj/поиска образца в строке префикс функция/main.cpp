#include <iostream>

using namespace std;

int main()
{
    const int MAX_STRING_LENGTH = 60000;
    char S[MAX_STRING_LENGTH];
    char T[MAX_STRING_LENGTH];
    char C[2 * MAX_STRING_LENGTH];
    int pi[2 * MAX_STRING_LENGTH] = {0};
    cin >> S;
    cin >> T;
    int lenT = 0;
    while (T[lenT] != '\0')
    {
        C[lenT] = T[lenT];
        ++lenT;
    }
    C[lenT] = '#';
    ++lenT;
    for (int i = 0; S[i] != '\0'; ++i)
        C[i + lenT] = S[i];
    pi[0] = 0;
    for (int i = 1; C[i] != '\0'; ++i)
    {
        int j = pi[i - 1];
        while (C[i] != C[j] && j > 0)
            j = pi[j - 1];
        if (C[i] == C[j])
        {
            ++j;
            if (j == lenT - 1)
                cout << i - 2 * lenT + 2 << ' ';
        }
        pi[i] = j;
    }
    return 0;
}
