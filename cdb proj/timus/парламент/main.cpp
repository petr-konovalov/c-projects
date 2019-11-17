#include <iostream>

using namespace std;

struct Tree
{
    int id;
    Tree *left;
    Tree *right;
};

void addTree(Tree **t, int id)
{
    if (*t)
    {
        if (id < (*t)->id)
            addTree(&(*t)->left, id);
        else
            addTree(&(*t)->right, id);
    }
    else
    {
        *t = new Tree;
        (*t)->id = id;
        (*t)->left = NULL;
        (*t)->right = NULL;
    }
}

void show(Tree *t)
{
    if (t)
    {
        show(t->right);
        show(t->left);
        cout << t->id << '\n';
    }
}

void clearTree(Tree **t)
{
    if (*t)
    {
        clearTree(&(*t)->left);
        clearTree(&(*t)->right);
        delete *t;
    }
}

int main()
{
    Tree *chairs = NULL;
    int numbers[3000];
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> numbers[i];

    for (int i = n - 1; i >= 0; --i)
        addTree(&chairs, numbers[i]);

    show(chairs);
    return 0;
}
