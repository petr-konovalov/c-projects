#include <stdio.h>
#include <vector>
#include <string.h>
#include <iomanip>

using namespace std;

struct Field
{
    char type;
    int link;
    Field(int type, int link): type(type), link(link) {};
};

struct Struct
{
    char name[11];
    vector<Field> fields;
    Struct(){};
    Struct(char *structName)
    {
        strcpy(name, structName);
    }
};

vector<Struct> s;
vector<int> table[240];

int getHash(char *str)
{
    unsigned long long h = 5381;
    int c;
    while (c = *str++)
        h = ((h << 5) + h) + c;
    return h % 240;
}

int getNumber(char *name)
{
    int h = getHash(name);
    for (int i = 0; i < table[h].size(); ++i)
        if (strcmp(s[table[h][i]].name, name) == 0)
            return table[h][i];
    return -1;
}

int decodeDigit(char digit)
{
    if ('0' <= digit && digit <= '9')
        return (int)(digit - '0');
    else if ('A' <= digit && digit <= 'F')
        return 10 + (int)(digit - 'A');
    return 0;
}

unsigned int get(char *&in, int cbyte)
{
    unsigned int res = 0;
    cbyte <<= 1;
    for (int i = 0; i < cbyte; ++i)
        res = res * 16 + decodeDigit(*in++);
    return res;
}

unsigned int getInt(char *&in)
{
    return get(in, 4);
}

char getChar(char *&in)
{
    return (char)get(in, 1);
}

char *decodeString(char *&in)
{
    unsigned int len = getInt(in);
    char *res = new char[len + 1];
    for (int i = 0; i < len; ++i)
        res[i] = getChar(in);
    res[len] = '\0';
    return res;
}

void decodeStruct(char *&in, unsigned int num, char *step, int dpt = 0)
{
    printf("%s%s\n", step, s[num].name);
    for (int i = 0; i < s[num].fields.size(); ++i)
    {
        if (s[num].fields[i].type == 1)
            printf("%s int %u\n", step, getInt(in));
        else if (s[num].fields[i].type == 2)
        {
            char *str = decodeString(in);
            printf("%s string %s\n", step, str);
            delete str;
        }
        else
        {
            step[dpt] = ' ';
            step[dpt + 1] = '\0';
            decodeStruct(in, s[num].fields[i].link, step, dpt + 1);
            step[dpt] = '\0';
        }
    }
}

int main()
{
    int n, l;
    scanf("%i %i", &n, &l);
    for (int i = 0; i < l; ++i)
    {
        char str[16];
        scanf("%s", str);
        if (strcmp(str, "struct") == 0)
        {
            char name[11];
            scanf("%s", name);
            table[getHash(name)].push_back(s.size());
            s.push_back(Struct(name));
        }
        else if (strcmp(str, "int") == 0)
            s.back().fields.push_back(Field(1, -1));
        else if (strcmp(str, "string") == 0)
            s.back().fields.push_back(Field(2, -1));
        else
            s.back().fields.push_back(Field(3, getNumber(str)));
    }
    char str[40001];
    scanf("%s", str);
    char *in = str;
    char step[256] = "";
    while (*in)
    {
        unsigned int num = getInt(in) - 1;
        decodeStruct(in, num, step);
    }
    return 0;
}
