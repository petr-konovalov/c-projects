#include <iostream>
#include <cstring>

#define NAME_LENGTH 32
#define MEMBER_COUNT 320

using namespace std;

struct List
{
    char value[NAME_LENGTH];
    List *next;
};

int addList(List **l, const char *value)
{
    if (!*l)
    {
        *l = new List;
        (*l)->next = NULL;
        strcpy((*l)->value, value);
        return 0;
    }
    else
    {
        List *node = *l;
        int pos = 0;
        while (node->next)
        {
            if (strcmp(node->value, value) == 0)
                return pos;
            ++pos;
            node = node->next;
        }
        if (strcmp(node->value, value) == 0)
            return pos;
        node->next = new List;
        node->next->next = NULL;
        strcpy(node->next->value, value);
        return pos + 1;
    }
}

int clearList(char names[MEMBER_COUNT][NAME_LENGTH], List **l)
{
    int id = 0;
    while (*l)
    {
        List *node = *l;
        *l = (*l)->next;
        strcpy(names[id++], node->value);
        delete node;
    }
    *l = NULL;
    return id;
}

void addLink(int i, int j, bool links[MEMBER_COUNT][MEMBER_COUNT])
{
    links[i][j] = true;
    links[j][i] = true;
}

void swapStr(char *first, char *second)
{
    char temp[NAME_LENGTH];
    strcpy(temp, first);
    strcpy(first, second);
    strcpy(second, temp);
}

void swapInt(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void calc(int m, bool links[MEMBER_COUNT][MEMBER_COUNT], int result[MEMBER_COUNT], int depth)
{
    if (depth < result[m])
    {
        result[m] = depth;
        for (int i = 0; i < MEMBER_COUNT; ++i)
        {
            if (links[m][i])
                calc(i, links, result, depth + 1);
        }
    }
}

int main()
{
    const int infinity = 10000;
    List *members = NULL;
    bool links[MEMBER_COUNT][MEMBER_COUNT] = {false};
    int result[MEMBER_COUNT];
    char names[MEMBER_COUNT][NAME_LENGTH];

    for (int i = 0; i < MEMBER_COUNT; ++i)
        result[i] = infinity;

    int n = 0;
    cin >> n;

    addList(&members, "Isenbaev");
    bool bb = false;
    for (int i = 0; i < n; ++i)
    {
        char a[NAME_LENGTH], b[NAME_LENGTH], c[NAME_LENGTH];
        cin >> a >> b >> c;
        int ia = addList(&members, a);
        int ib = addList(&members, b);
        int ic = addList(&members, c);
        addLink(ia, ib, links);
        addLink(ia, ic, links);
        addLink(ib, ic, links);
        if (!bb && (strcmp(a, "Isenbaev") == 0 || strcmp(b, "Isenbaev") == 0 || strcmp(c, "Isenbaev") == 0))
            bb = true;
    }

    int c = clearList(names, &members);
    if (bb)
        calc(0, links, result, 0);
    else
    {
        --c;
        for (int i = 0; i < c; ++i)
            strcpy(names[i], names[i + 1]);
    }

    for (int i = 1; i < c; ++i)
    {
        for (int j = i; j > 0 && strcmp(names[j], names[j - 1]) < 0; --j)
        {
            swapStr(names[j], names[j - 1]);
            swapInt(result[j], result[j - 1]);
        }
    }

    for (int i = 0; i < c; ++i)
        if (result[i] == infinity)
            cout << names[i] << ' ' << "undefined\n";
        else
            cout << names[i] << ' ' << result[i] << '\n';
    return 0;
}
