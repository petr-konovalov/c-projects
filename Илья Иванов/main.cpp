#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    ifstream rf(argv[1]);
    string str;
    int sumLen = 0;
    int cnt = 0;
    while (rf >> str)
    {
      ++cnt;
      sumLen += str.length();
    }
    cout << "Mean length: " << (double)sumLen / cnt << endl;
    rf.close();
    return 0;
}
