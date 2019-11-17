#include <iostream>

using namespace std;

int t[14];

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        int num;
        cin >> num;
        ++t[num];
    }
    for (int i = 1; i <= 13; ++i)
        if (t[i] == 5)
        {
            cout << "Impossible";
            return 0;
        }
    for (int i = 1; i <= 13; ++i)
        if (t[i] == 4)
        {
            cout << "Four of a Kind";
            return 0;
        }
    for (int i = 1; i <= 13; ++i)
    {
        if (t[i] == 3)
        {
            for (int j = 1; j <= 13; ++j)
                if (t[j] == 2)
                {
                    cout << "Full House";
                    return 0;
                }
            break;
        }
    }
    for (int i = 1; i <= 9; ++i)
    {
        if (t[i] == 1 && t[i + 1] == 1 && t[i + 2] == 1 && t[i + 3] == 1 && t[i + 4] == 1)
        {
            cout << "Straight";
            return 0;
        }
    }
    for (int i = 1; i <= 13; ++i)
        if (t[i] == 3)
        {
            cout << "Three of a Kind";
            return 0;
        }
    for (int i = 1; i <= 13; ++i)
    {
        if (t[i] == 2)
        {
            for (int j = 1; j <= 13; ++j)
                if (i != j && t[j] == 2)
                {
                    cout << "Two Pairs";
                    return 0;
                }
            break;
        }
    }
    for (int i = 1; i <= 13; ++i)
        if (t[i] == 2)
        {
            cout << "One Pair";
            return 0;
        }
    cout << "Nothing";
    return 0;
}
