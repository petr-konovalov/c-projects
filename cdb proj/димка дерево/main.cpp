#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>

using namespace std;

typedef struct link {
int id;
int weight;
struct link *left, *right;
} tree;

void add(tree **t, int x,int y) {
if (*t == NULL) {
*t = new(tree);
(*t)->id = x;
(*t)->weight = y;
(*t)->left = NULL;
(*t)->right = NULL;
}
else if (x<(*t)->id) add(&(*t)->left, x, y);
else add(&(*t)->right, x, y);
}

void show(tree *t, int n) {
if (t != NULL) {
show(t->left, n + 1);
cout << setw(n * 4) << t->id << "(" << t->weight << ")" << endl;
show(t->right, n + 1);
}
}

void Search(tree *t) {
if (t!=NULL)
{
if ((t->weight==0) && (t->id)%2==0) {
cout << t->id << "(" << t->weight << ")" << " has weight 0" << endl;
//exit(0);
}
Search(t->left);
Search(t->right);
}
}
void del(tree **t, int x) {
tree *p, *r;
if (*t != NULL)
if ((*t)->id > x) del(&(*t)->left, x);
else if ((*t)->id < x) del(&(*t)->right, x);
else if ((*t)->id != x) { cout << "err" << endl; return; }
else {
if ((*t)->left == NULL && (*t)->right == NULL) { p = *t; *t = NULL; }
else if ((*t)->left == NULL) { p = *t; *t = (*t)->right; }
else if ((*t)->right == NULL) { p = *t; *t = (*t)->left; }
else {
r = (*t)->left;
if (r->right != NULL) {
while (r->right->right != NULL) r = r->right;
(*t)->id = r->right->id;
p = r->right;
r->right = r->right->left;
}
else {
(*t)->id = r->id;
(*t)->left = (*t)->left->left;
}
}
delete(p);
}
}
int main()
{
int a, z;
tree *tmp = NULL;
srand(time(0));
for (int i = 0; i < 10; i++) add(&tmp, rand() % 10 + 1,rand()%3-1);
show(tmp, 1);
Search(tmp);
do {
cout << "1-add" << endl << "2-show" << endl << "3-del" << endl << "0-exit" << endl;
cin >> a;
switch (a)
{
case 1: cout <<"id = ?"; cin >> z; add(&tmp, z, 0); break;
case 2: show(tmp, 1); break;
case 3: cout <<"id = ?"; cin >> z; del(&tmp, z); break;

}
} while (a);
return 0;
}
