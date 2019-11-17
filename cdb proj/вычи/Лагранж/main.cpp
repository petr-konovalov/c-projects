#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;
const double a = 0, b = PI;
const int n = 20;

double f(double x)
{
    return sin(x / 3);
}

double g(double x)
{
    return sin(10 * x);
}

double d(double x)
{
    return sin(8 * x);
}

double omegak(int k, double x, vector<double> node)
{
    double res = 1;

    for (int i = 0; i < k; ++i)
        res *= x - node[i];

    for (int i = k + 1; i < node.size(); ++i)
        res *= x - node[i];

    return res;
}

double omega(double x, vector<double> node)
{
    double res = 1;

    for (int i = 0; i < node.size(); ++i)
        res *= x - node[i];

    return res;
}

double derOmega(int k, vector<double> node)
{
    return omegak(k, node[k], node);
}

double calcLagrang(double x, vector<double> node, vector<double> value)
{
    double res = 0;

    for (int i = 0; i < node.size(); ++i)
        res += omegak(i, x, node) * value[i] / derOmega(i, node);

    return res;
}

void printTable(double (*f)(double), double maxDer, vector<double> node)
{
    double fact = 1;
    vector<double> value;

    for (int i = 2; i <= node.size(); ++i)
        fact *= i;

    printf("Nodes: ");
    for (int i = 0; i < node.size(); ++i)
    {
        printf("%15.8f", node[i]);
        value.push_back(f(node[i]));
    }
    printf("\n");

    printf("%25s%25s%25s%25s%40s\n", "xj   ", "f(xj)  ", "L(xj)  ", "|R(x, f)|", "A    ");
    for (double cur = a, h = (b - a) / n; cur <= b; cur += h)
    {
        double fval = f(cur), Lval = calcLagrang(cur, node, value);
        printf("%25.8f%25.8f%25.8f%25.8f%40.8f\n", cur, fval, Lval, abs(fval - Lval),
               abs(omega(cur, node)) * maxDer / fact);
    }
    printf("\n");
}

void printTable(double (*f)(double), double maxDer)
{
    vector<double> node;

    node.push_back(PI / 4);
    node.push_back(PI / 2);
    node.push_back(PI);
    node.push_back(2 * PI);
    node.push_back(3 * PI);
    printTable(f, maxDer, node);

    node.clear();
    node.push_back(PI / 6);
    node.push_back(PI / 2);
    node.push_back(PI);
    node.push_back(5 * PI / 6);
    node.push_back(3 * PI / 2);
    printTable(f, maxDer, node);

    node.clear();
    node.push_back(5 * PI / 3);
    node.push_back(2 * PI);
    node.push_back(9 * PI / 4);
    node.push_back(5 * PI / 2);
    node.push_back(17 * PI / 6);
    printTable(f, maxDer, node);

    node.clear();
    node.push_back(3 * PI / 4);
    node.push_back(PI);
    node.push_back(4 * PI / 3);
    node.push_back(11 * PI / 6);
    node.push_back(13 * PI / 6);
    printTable(f, maxDer, node);

    node.clear();
    node.push_back(PI / 4);
    node.push_back(PI / 2);
    node.push_back(PI);
    node.push_back(7 * PI / 6);
    node.push_back(3 * PI / 2);
    node.push_back(7 * PI / 4);
    node.push_back(2 * PI);
    node.push_back(7 * PI / 3);
    node.push_back(17 * PI / 6);
    node.push_back(3 * PI);
    printTable(f, maxDer * maxDer, node);
}

int main()
{
    freopen("output.txt", "w", stdout);
    printf("First function table:\n");
    printTable(f, (double)1 / 243);
    printf("\nSecond function table:\n");
    printTable(g, 1e5);
    return 0;
}
