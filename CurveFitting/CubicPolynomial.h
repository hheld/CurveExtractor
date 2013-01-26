#ifndef CUBICPOLYNOMIAL_H
#define CUBICPOLYNOMIAL_H

#include "LeastSquaresSolver.h"

class CubicPolynomial : public LeastSquaresSolver
{
public:
    CubicPolynomial();

    void prepareProblem();
    double operator()(const double &x) const;

private:
    double a;
    double b;
    double c;
    double d;
};

#endif // CUBICPOLYNOMIAL_H
