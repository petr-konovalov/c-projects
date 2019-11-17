#include <iostream>

using namespace std;

int main()
{
    char str1[2010] = "";
    char str2[2010] = "";
    int lenStr1 = 0;
    int lenStr2 = 0;
    cin >> str1;
    cin >> str2;
    while (str1[lenStr1] != '\0')
        ++lenStr1;
    while (str2[lenStr2] != '\0')
        ++lenStr2;
    int **a = new int*[lenStr1];
    for (int i = 0; i < lenStr1; ++i)
        a[i] = new int[lenStr2];
    for (int i = 0 ; i < lenStr1; ++i)
    {
        for (int j = 0; j < lenStr2; ++j)
            a[i][j] = 0;
    }
    for (int i = 0; i < lenStr2; ++i)
    {
        if (str1[0] == str2[i])
            a[0][i] = 1;
    }
    for (int i = 0; i < lenStr1; ++i)
    {
        if (str2[0] == str1[i])
            a[i][0] = 1;
    }
    for (int i = 1; i < lenStr1; ++i)
    {

        for (int j = 1; j < lenStr2; ++j)
            if (str1[i] == str2[j])
                a[i][j] = a[i - 1][j - 1] + 1;
            else
                a[i][j] = 0;
    }
    int maxs[lenStr1] = {0};
    int idl[lenStr1] = {0};
    int idr[lenStr1] = {0};
    for (int i = 0; i < lenStr1; ++i)
    {
        for (int j = 0; j < lenStr2; ++j)
        {
            if (a[i][j] > maxs[i])
            {
                maxs[i] = a[i][j];
                idl[i] = j;
            }
            if (a[i][j] == maxs[i])
                idr[i] = j;
        }
    }
    int mA = -1, mB = -1, md = -1;
    for (int i = 0; i < lenStr1; ++i)
    {
        if (maxs[i] > md)
        {
            md = maxs[i];
            mA = i;
            mB = -1;
        }
        for (int j = i + 1; j < lenStr1; ++j)
        {
            if (j - maxs[j] >= i && idr[j] - maxs[j] >= idl[i] && maxs[i] + maxs[j] > md)
            {
                md = maxs[i] + maxs[j];
                mA = i;
                mB = j;
            }
        }
    }
    if (mA != -1)
    {
        for (int i = mA - maxs[mA] + 1; i <= mA; ++i)
            cout << str1[i];
        cout << '\n';
    }
    if (mB != -1)
    {
        for (int i = mB - maxs[mB] + 1; i <= mB; ++i)
            cout << str1[i];
    }
    return 0;
}
