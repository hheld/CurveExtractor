#include "LeastSquaresSolver.h"
#include "QuadraticPolynomialResidual.h"
#include "ceres/ceres.h"

using ceres::AutoDiffCostFunction;
using ceres::Problem;
using ceres::Solver;

LeastSquaresSolver::LeastSquaresSolver() :
    a(0.),
    b(0.),
    c(0.)
{
}

void LeastSquaresSolver::setDataPoints(const QVector<double> &xData, const QVector<double> &yData)
{
    this->xData = xData;
    this->yData = yData;
}

void LeastSquaresSolver::solve()
{
    Problem problem;

    a = 0.;
    b = 0.;
    c = 0.;

    int numOfObservations = xData.size();

    Q_ASSERT(yData.size() == numOfObservations);

    for (int i=0; i<numOfObservations; ++i)
    {
        problem.AddResidualBlock(new AutoDiffCostFunction<QuadraticPolynomialResidual, 1, 1, 1, 1>(new QuadraticPolynomialResidual(xData[i], yData[i])), 0, &a, &b, &c);
    }

    Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    Solver::Summary summary;
    Solve(options, &problem, &summary);

    std::cout << summary.BriefReport() << std::endl;
}

double LeastSquaresSolver::operator ()(const double &x) const
{
    return a*x*x + b*x + c;
}
