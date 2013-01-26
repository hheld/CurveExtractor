#include "QuadraticPolynomial.h"
#include "QuadraticPolynomialResidual.h"
#include "ceres/ceres.h"

using ceres::AutoDiffCostFunction;

QuadraticPolynomial::QuadraticPolynomial() :
    LeastSquaresSolver()
{
}

void QuadraticPolynomial::prepareProblem()
{
    a = 0.;
    b = 0.;
    c = 0.;

    int numOfObservations = xData.size();

    Q_ASSERT(yData.size() == numOfObservations);

    for (int i=0; i<numOfObservations; ++i)
    {
        problem->AddResidualBlock(new AutoDiffCostFunction<QuadraticPolynomialResidual, 1, 1, 1, 1>(new QuadraticPolynomialResidual(xData[i], yData[i])), 0, &a, &b, &c);
    }
}

double QuadraticPolynomial::operator ()(const double &x) const
{
    return a*x*x + b*x + c;
}
