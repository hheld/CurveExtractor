#include "LeastSquareSolverFactory.h"
#include "LeastSquaresSolver.h"
#include "QuadraticPolynomial.h"
#include "CubicPolynomial.h"

LeastSquaresSolver *LeastSquareSolverFactory::getSolver(const LeastSquareSolverFactory::curve_t &type)
{
    LeastSquaresSolver *solver = 0;

    switch(type)
    {
    case PolyQuadratic:
        solver = new QuadraticPolynomial;
        break;
    case PolyCubic:
        solver = new CubicPolynomial;
        break;
    }

    return solver;
}

LeastSquareSolverFactory::LeastSquareSolverFactory()
{
}
