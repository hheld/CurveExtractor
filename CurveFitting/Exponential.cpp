#include "Exponential.h"
#include "ExponentialResidual.h"
#include "ceres/ceres.h"

using ceres::AutoDiffCostFunction;

Exponential::Exponential() :
    LeastSquaresSolver()
{
}

void Exponential::prepareProblem()
{
    a = 0.;
    b = 0.;
    c = 0.;

    int numOfObservations = xData.size();

    Q_ASSERT(yData.size() == numOfObservations);

    for (int i=0; i<numOfObservations; ++i)
    {
        problem->AddResidualBlock(new AutoDiffCostFunction<ExponentialResidual, 1, 1, 1, 1>(new ExponentialResidual(xData[i], yData[i])), 0, &a, &b, &c);
    }
}

double Exponential::operator ()(const double &x) const
{
    return a*exp(b*x*x + c);
}
