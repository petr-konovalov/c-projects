#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>

#define EPS 0.000001
//#define N 0.001

int kol=0;

using namespace std;

double f (double x, double y, double k)
    {
       return cosh(k*x*x+y)-x+y-1;
    }
double der_f_x(double x, double y, double k)
    {
        return 2*x*k*sinh(k*x*x+y)-1;
    }
double der_f_y(double x, double y, double k)
    {
        return sinh(k*x*x+y)+1;
    }
double g (double x, double y, double a)
    {
       return pow((x-0.1),2)/(a*a)-y*y/2-0.8;
    }
double der_g_x(double x, double y, double a)
    {
        return 2*(x-0.1)/(a*a);
    }
double der_g_y(double x, double y, double a)
    {
        return -y;
    }
double kramer_X(double x, double y, double k,double a)
    {
        double F=f(x,y,k);
        double G=g(x,y,a);
        double f_x=der_f_x(x,y,k);
        double f_y=der_f_y(x,y,k);
        double g_x=der_g_x(x,y,a);
        double g_y=der_g_y(x,y,a);
        double X;

        X=(-F*g_y+G*f_y)/(f_x*g_y-g_x*f_y);

        return X;
    }
double kramer_Y(double x, double y, double k, double a)
    {
        double F=f(x,y,k);
        double G=g(x,y,a);
        double f_x=der_f_x(x,y,k);
        double f_y=der_f_y(x,y,k);
        double g_x=der_g_x(x,y,a);
        double g_y=der_g_y(x,y,a);
        double Y;

        Y=(-f_x*G+g_x*F)/(f_x*g_y-g_x*f_y);

        return Y;
    }

pair <double,double> StartApproximate(double A, double B, double k, double a)
    {
        double N=(B-A)/1000;
        double x1=A;
        double x2=A+N;
        double y1=A;
        double y2=A+N;

        while (x2<=B)
            {
                while (y2<=B)
                    {
                        if ((fabs(f(x1,y1,k))<=0.1) && (fabs(g(x1,y1,a))<=0.1))
                            return pair <double,double>(x1,y1);
                            else
                            {
                                y1=y2;
                                y2=y1+N;
                            }
                    }
                    x1=x2;
                    x2=x1+N;
                    y1=A;
                    y2=y1+N;
            }
        return pair <double,double>(100,100);
    }
void Approximate(pair <double,double> start_a,double k,double a)
    {
        FILE *myfile;
        myfile = fopen("out.txt","a");
        int num=0;
        double x1,y1;
        double x0=start_a.first;
        double y0=start_a.second;
        fprintf(myfile,"%.1f %.1f \n \n",k,a);
        fprintf(myfile,"%d %.7f %.7f %.7f %.7f \n",num,x0,y0,f(x0,y0,k),g(x0,y0,a));
        x1=x0+kramer_X(x0,y0,k,a);
        y1=y0+kramer_Y(x0,y0,k,a);
        while ((fabs(x1-x0)>EPS) && (fabs(y1-y0)>EPS))
            {
                num++;
                x0=x1;
                y0=y1;
                x1=x0+kramer_X(x0,y0,k,a);
                y1=y0+kramer_Y(x0,y0,k,a);
                fprintf(myfile,"%d %.7f %.7f %.7f %.7f \n",num,x0,y0,f(x0,y0,k),g(x0,y0,a));
            }
                num++;
                fprintf(myfile,"%d %.7f %.7f %.7f %.7f \n \n",num,x1,y1,f(x1,y1,k),g(x1,y1,a));
        fclose(myfile);
    }
void separate(double A,double B, double k, double a, pair <double,double> start_a)
    {
            FILE *myfile;
            myfile = fopen("out.txt","a");
            if (StartApproximate(A,B,k,a)!=make_pair(100.0,100.0))
            {
                kol++;
                fprintf(myfile,"%d: \n",kol);
                fflush(myfile);
                Approximate(start_a,k,a);
                fprintf(myfile,"\n \n");
                A=max(StartApproximate(A,B,k,a).first,StartApproximate(A,B,k,a).second)+fabs((B-A)/100);
                separate(A,B,k,a,StartApproximate(A,B,k,a));
            }
            fclose(myfile);
    }
void ForAll_a_and_k(double A,double B)
    {
        double a,k;
        for (a=0.7;a<=1.2;a+=0.1)
            for (k=0.1;k<=0.5;k+=0.1)
            {
                pair <double,double> start_a=StartApproximate(A,B,k,a);
                if (StartApproximate(A,B,k,a)!=make_pair(100.0,100.0))
                    separate(A,B,k,a,start_a);
            }
    }

int main()
{
        ForAll_a_and_k(-10,10);

    return 0;
}
