#include "LeastSquaresSolver.h"

#include "ceres/ceres.h"

using ceres::Solver;

LeastSquaresSolver::LeastSquaresSolver():
    problem(new ceres::Problem)
{
}

LeastSquaresSolver::~LeastSquaresSolver()
{
    delete problem;
}

void LeastSquaresSolver::setDataPoints(const QVector<double> &xData, const QVector<double> &yData)
{
    this->xData = xData;
    this->yData = yData;

    prepareProblem();
}

void LeastSquaresSolver::solve()
{
    Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    Solver::Summary summary;
    Solve(options, problem, &summary);

    std::cout << summary.BriefReport() << std::endl;
}
