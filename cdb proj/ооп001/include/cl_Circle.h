#ifndef CL_CIRCLE_H
#define CL_CIRCLE_H
#include "clDraw.h"


class cl_Circle: public clDraw
{
    public:
        cl_Circle();
        cl_Circle(int x, int y, int r): x(x), y(y), r(r){};
        virtual ~cl_Circle();

        int Getx() { return x; }
        void Setx(int val) { x = val; }
        int Gety() { return y; }
        void Sety(int val) { y = val; }
        int Getr() { return r; }
        void Setr(int val) { r = val; }
        void Show();

    protected:

    private:
        int x;
        int y;
        int r;
};

#endif // CL_CIRCLE_H
