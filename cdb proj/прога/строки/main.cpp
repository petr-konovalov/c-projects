#include <iostream>
#include <string>

using namespace std;

int main()
{
    string in;
    string out;
    bool used[256] = {false};
    getline(cin, in);
    for (char c: in)
        if (!used[c])
        {
            out += c;
            used[c] = true;
        }
    cout << out;
    return 0;
}
