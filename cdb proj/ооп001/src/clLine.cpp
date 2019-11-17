#include "clLine.h"

clLine::clLine()
{
    //ctor
}

clLine::~clLine()
{
    //dtor
}

void clLine::Show()
{
    line(xa, ya, xb, yb);
}
