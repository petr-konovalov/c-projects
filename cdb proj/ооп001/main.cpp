#include <iostream>
#include <graphics.h>
#include "cl_Circle.h"
#include "clLine.h"
#include "clNode.h"

using namespace std;

int main()
{
    int gd = DETECT;
    int gm;
    initgraph(&gd, &gm,"");
    clNode firstNode(20, 20, 15, 10);
    clNode secondNode(100, 100, 30, 20);
    firstNode.Show();
    secondNode.Show();
    cin.get();
    return 0;
}
