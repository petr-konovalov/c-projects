#ifndef CLNODE_H
#define CLNODE_H

#include "cl_Circle.h"
#include <cstdlib>


class clNode : public cl_Circle
{
    public:
        clNode();
        clNode(int x, int y, int r, int value);
        virtual ~clNode();

        char* GetNum() { return num; }
        void Setnum(int value) { itoa(value, num, 10); }
        void Show();
    protected:

    private:
        char* num;
};

#endif // CLNODE_H
