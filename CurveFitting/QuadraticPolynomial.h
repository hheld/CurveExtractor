#ifndef QUADRATICPOLYNOMIAL_H
#define QUADRATICPOLYNOMIAL_H

#include "LeastSquaresSolver.h"

class QuadraticPolynomial : public LeastSquaresSolver
{
public:
    QuadraticPolynomial();

    void prepareProblem();
    double operator()(const double &x) const;

private:
    double a;
    double b;
    double c;
};

#endif // QUADRATICPOLYNOMIAL_H
