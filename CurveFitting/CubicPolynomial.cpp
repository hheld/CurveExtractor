#include "CubicPolynomial.h"
#include "CubicPolynomialResidual.h"
#include "ceres/ceres.h"

using ceres::AutoDiffCostFunction;

CubicPolynomial::CubicPolynomial() :
    LeastSquaresSolver()
{
}

void CubicPolynomial::prepareProblem()
{
    a = 0.;
    b = 0.;
    c = 0.;
    d = 0.;

    int numOfObservations = xData.size();

    Q_ASSERT(yData.size() == numOfObservations);

    for (int i=0; i<numOfObservations; ++i)
    {
        problem->AddResidualBlock(new AutoDiffCostFunction<CubicPolynomialResidual, 1, 1, 1, 1, 1>(new CubicPolynomialResidual(xData[i], yData[i])), 0, &a, &b, &c, &d);
    }
}

double CubicPolynomial::operator ()(const double &x) const
{
    return a*x*x*x + b*x*x + c*x + d;
}
