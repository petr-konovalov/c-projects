#include <stdio.h>
#include <vector>
#include <string.h>
#include <windows.h>
#include <algorithm>

using namespace std;

const int permitLen = 25;

struct Word
{
    char value[permitLen + 1];
    Word(){}
    Word(int len, char *word)
    {
        for (int i = 0; i < len; ++i)
            value[i] = word[i];
        value[len] = '\0';
    }
};

struct State
{
    bool isTerminate;
    int next[33];
    State()
    {
        isTerminate = false;
        for (int i = 0; i < 33; ++i)
            next[i] = -1;
    }
};

int number[256] = {0};
char alth[64];
vector<State> t;
char field[5][5];
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
bool used[5][5];

bool format(char *word)
{
    int i = 0;
    while (word[i] != '\n' && word[i] != '\0')
    {
        if (number[(unsigned char)word[i]])
            ++i;
        else
            return false;
    }
    if (i > permitLen || i < 2)
        return false;
    word[i] = '\0';
    return true;
}

vector<Word> init()
{
    FILE *dict = fopen("words.txt", "r");
    char word[64];
    vector<Word> words;
    fgets(alth, 63, dict);
    for (int i = 0; alth[i] != '\0' && alth[i] != '\n'; ++i)
        number[(unsigned char)alth[i]] = i + 1;
    while (fgets(word, 63, dict))
    {
        Word str;
        if (format(word))
        {
            strcpy(str.value, word);
            words.push_back(str);
        }
    }
    fclose(dict);
    return words;
}

void makeTable(vector<Word> words)
{
    t.push_back(State());
    for (int i = 0; i < words.size(); ++i)
    {
        int state = 0;
        for (int k = 0; words[i].value[k] != '\0'; ++k)
        {
            int num = number[(unsigned char)words[i].value[k]] - 1;
            int nextState = t[state].next[num];
            if (nextState == -1)
            {
                t.push_back(State());
                nextState = t.size() - 1;
                t[state].next[num] = nextState;
            }
            state = nextState;
        }
        t[state].isTerminate = true;
    }
}

vector<Word> ans;

bool operator< (Word a, Word b)
{
    return strcmp(a.value, b.value) < 0;
}

bool operator== (Word a, Word b)
{
    return strcmp(a.value, b.value) == 0;
}

void findWords(int dpt, int state, char *word,
               bool emptyVisit, int x, int y)
{
    if (state == -1 || dpt > permitLen)
        return;
    if (emptyVisit && t[state].isTerminate)
        ans.push_back(Word(dpt, word));
    used[x][y] = true;
    for (int i = 0; i < 4; ++i)
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (tx >= 0 && tx <= 4 && ty >= 0 && ty <= 4 && !used[tx][ty])
            if (field[tx][ty] != '.')
            {
                word[dpt] = field[tx][ty];
                findWords(dpt + 1, t[state].next[number[(unsigned char)field[tx][ty]] - 1], word,
                          emptyVisit, tx, ty);
            }
            else if (!emptyVisit)
            {
                for (int j = 0; alth[j] != '\0' && alth[j] != '\n'; ++j)
                {
                    word[dpt] = alth[j];
                    findWords(dpt + 1, t[state].next[number[(unsigned char)alth[j]] - 1], word,
                              true, tx, ty);
                }
            }
    }
    used[x][y] = false;
}

bool lenComp(Word a, Word b)
{
    return strlen(a.value) < strlen(b.value);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Word> words = init();
    makeTable(words);
    printf("%u\n", t.size());
    for (int i = 0; i < 5; ++i)
    {
        char str[16];
        scanf("%s", str);
        for (int j = 0; j < 5; ++j)
            field[i][j] = str[j];
    }
    char word[permitLen + 1];
    for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
            findWords(0, 0, word, false, x, y);
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    stable_sort(ans.begin(), ans.end(), lenComp);
    for (int i = 0; i < ans.size(); ++i)
        printf("%s\n", ans[i].value);
    printf("\nclick to enter\n");
    getc(stdin);
    getc(stdin);
    return 0;
}
