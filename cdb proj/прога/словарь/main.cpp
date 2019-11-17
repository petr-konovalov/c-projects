#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;

list<string> split(string str, bool *delim)
{
    list<string> res;
    string cur;
    for (char c: str)
    {
        if (delim[c])
        {
            if (cur != "")
            {
                res.push_back(cur);
                cur = "";
            }
        }
        else
            cur += c;
    }
    res.push_back(cur);
    return res;
}

int main()
{
    map<string, list<string> > dict;
    int n = 0;
    bool delim[256] = {false};
    delim[' '] = true;
    delim[','] = true;
    delim['-'] = true;
    cin >> n;
    while (n--)
    {
        string in;
        cin >> in;
        string translates;
        getline(cin, translates);
        list<string> words = split(translates, delim);
        for (auto word: words)
            dict[word].push_back(in);
    }
    cout << dict.size() << endl;
    for (auto v: dict)
    {
        cout << v.first << " - ";
        auto t = v.second.begin();
        cout << *t;
        ++t;
        while(t != v.second.end())
        {
            cout << ", " << *t;
            ++t;
        }
        cout << endl;
    }
    return 0;
}
