#ifndef LEASTSQUARESOLVERFACTORY_H
#define LEASTSQUARESOLVERFACTORY_H

class LeastSquaresSolver;

class LeastSquareSolverFactory
{
public:
    enum curve_t
    {
        PolyQuadratic,
        PolyCubic/*,
        Exp*/
    };

    static LeastSquaresSolver* getSolver(const curve_t &type);

private:
    LeastSquareSolverFactory();
};

#endif // LEASTSQUARESOLVERFACTORY_H
