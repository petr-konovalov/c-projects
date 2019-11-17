#include <iostream>
#include <cmath>

using namespace std;

typedef struct Complex
{
    double re;
    double im;
    Complex(double re, double im): re(re), im(im){};
    Complex(){re = 0; im = 0;};
} Complex;

Complex conjugate(const Complex &a)
{
    return Complex(a.re, -a.im);
}

double abs(const Complex &a)
{
    return sqrt(a.re * a.re + a.im * a.im);
}

Complex operator+ (const Complex &a, const Complex &b)
{
    return Complex(a.re + b.re, a.im + b.im);
}

Complex operator- (const Complex &a, const Complex &b)
{
    return Complex(a.re - b.re, a.im - b.im);
}

Complex operator* (const Complex &a, const Complex &b)
{
    return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}

Complex operator* (const Complex &a, const double &b)
{
    return Complex(a.re * b, a.im * b);
}

Complex operator/ (const Complex &a, const double &b)
{
    return Complex(a.re / b, a.im / b);
}

Complex operator/ (const Complex &a, const Complex &b)
{
    return a * conjugate(b) / abs(b);
}

Complex func(Complex a)
{
    return a * a * a * a - a * a * a * 18 + a * 1944 - Complex(11664, 0);
}

int main()
{
    const double eps = 1e-3;
    const double step = 1;
    for (double i = -1000; i <= 1000; i += step)
        for (double j = 0; j <= 1000; j += step)
        {
            Complex cur = func(Complex(i, j));
            //cout << cur.re << ' ' << cur.im << '\n';
            if (abs(cur.re) < eps && abs(cur.im) < eps)
            {
                cout << i << '+' << j << 'i' << '\n';
                cout << i << '-' << j << 'i';
                return 0;
            }
        }
    return 0;
}
