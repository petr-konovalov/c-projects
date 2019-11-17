#include <iostream>
#include <cmath>

#define MAX_STRING_LENGTH 1024

using namespace std;

void printPolygon(const double *poly, const int deg)
{
    for (int i = 0; i <= deg; ++i)
        cout << poly[i] << ' ';
    cout << endl;
}

double *getDerivative(const double *poly, int deg)
{
    double *derivative = new double[deg];

    for (int i = 0; i < deg; ++i)
        derivative[i] = poly[i + 1] * (i + 1);

    return derivative;
}

double getPolygonValue(const double *poly, const int deg, const double arg)
{
    double value = 0;

    for (int i = deg; i >= 0; --i)
        value = value * arg + poly[i];

    return value;
}

double searchPolygonDecision(const double *poly, const int deg, double left, double right)
{
    const double eps = 1e-10 ;
    double decision = (left + right) / 2;

    if (getPolygonValue(poly, deg, left) >= 0 && 0 >= getPolygonValue(poly, deg, right))
    {
        while (right - left > eps)
        {
            if (getPolygonValue(poly, deg, decision) > 0)
                left = decision;
            else
                right = decision;

            decision = (left + right) / 2;
        }
        return right;
    }
    else
    if (getPolygonValue(poly, deg, left) <= 0 && 0 <= getPolygonValue(poly, deg, right))
    {
        while (right - left > eps)
        {
            if (getPolygonValue(poly, deg, decision) > 0)
                right = decision;
            else
                left = decision;

            decision = (left + right) / 2;
        }
        return left;
    }

    return decision;
}

double *getDecision(const double *poly, const int deg, int *decisionCount, const double left, const double right)
{
    const double eps = 1e-7;
    double *derivative = getDerivative(poly, deg);
    double *oldDecision;
    int oldDecisionCount = 1;

    if (deg > 1)
        oldDecision = getDecision(derivative, deg - 1, &oldDecisionCount, left, right);
    else if (deg == 1)
    {
        *decisionCount = 3;
        double *newDecision = new double[3];

        newDecision[0] = left;
        newDecision[1] = -poly[0]/poly[1];
        newDecision[2] = right;

        return newDecision;
    }
    delete[] derivative;

    double *newDecision = new double[oldDecisionCount + 1];

    *decisionCount = 1;
    for (int i = 0; i < oldDecisionCount - 1; ++i)
    {
        double decision = searchPolygonDecision(poly, deg, oldDecision[i], oldDecision[i + 1]);

        if (abs(getPolygonValue(poly, deg, decision)) < eps)
        {
            newDecision[*decisionCount] = decision;
            *decisionCount += 1;
        }
    }
    newDecision[0] = left;
    newDecision[*decisionCount] = right;
    *decisionCount += 1;

    delete[] oldDecision;
    return newDecision;
}

int main()
{
    int deg = 0;
    int decisionCount = 0;

    cin >> deg;
    double *poly = new double[deg + 1];
    double *decision;

    for (int i = 0; i <= deg; ++i)
        cin >> poly[i];

    decision = getDecision(poly, deg, &decisionCount, -15, 15);
    for (int i = 1; i < decisionCount - 1; ++i)
        cout << decision[i] << ' ';
    delete decision;
    return 0;
}
