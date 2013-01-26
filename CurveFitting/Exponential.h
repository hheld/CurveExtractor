#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include "LeastSquaresSolver.h"

class Exponential : public LeastSquaresSolver
{
public:
    Exponential();

    void prepareProblem();
    double operator()(const double &x) const;

private:
    double a;
    double b;
    double c;
};

#endif // EXPONENTIAL_H
