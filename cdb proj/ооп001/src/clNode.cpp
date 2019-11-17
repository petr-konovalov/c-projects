#include "clNode.h"

clNode::clNode()
{
    //ctor
    num = new char[8];
}

clNode::clNode(int x, int y, int r, int value): cl_Circle(x, y, r), num(new char[8])
{
    Setnum(value);
}

clNode::~clNode()
{
    //dtor
    delete num;
}

void clNode::Show()
{
    cl_Circle::Show();
    outtextxy(Getx() - textwidth(num) / 2, Gety() - textheight(num) / 2, num);
}
