#ifndef CLLINE_H
#define CLLINE_H
#include "clDraw.h"

class clLine: public clDraw
{
    public:
        clLine();
        clLine(int xa, int ya, int xb, int yb): xa(xa), ya(ya), xb(xb), yb(yb){};
        virtual ~clLine();

        int Getxa() { return xa; }
        void Setxa(int val) { xa = val; }
        int Getya() { return ya; }
        void Setya(int val) { ya = val; }
        int Getxb() { return xb; }
        void Setxb(int val) { xb = val; }
        int Getyb() { return yb; }
        void Setyb(int val) { yb = val; }
        void Show();

    protected:

    private:
        int xa;
        int ya;
        int xb;
        int yb;
};

#endif // CLLINE_H
