#include <iostream>

using namespace std;

unsigned lineCount(const unsigned *L, const unsigned lineCount, const unsigned lineLength)
{
    unsigned result = 0;
    for (unsigned i = 0; i < lineCount; ++i)
        result += L[i] / lineLength;
    return result;
}

int main()
{
    const unsigned maxLineLength = 10000001;
    const unsigned maxLineCount = 10000;
    unsigned L[maxLineCount] = {0};
    unsigned N = 0;
    unsigned K = 0;
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> L[i];
    unsigned l = 0;
    unsigned r = maxLineLength;
    while ((r - l) > 1)
    {
        unsigned m = (l + r) / 2;
        if (lineCount(L, N, m) < K)
            r = m;
        else
            l = m;
    }
    cout << l;
    return 0;
}
