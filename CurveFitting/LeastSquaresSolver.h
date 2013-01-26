#ifndef LEASTSQUARESSOLVER_H
#define LEASTSQUARESSOLVER_H

#include <QVector>

namespace ceres
{
    class Problem;
}

/**
 * The LeastSquaresSolver class fits a quadratic polynomial y=a*x^2+b*x+c to given measurement data pairs (x,y).
 */
class LeastSquaresSolver
{
public:
    LeastSquaresSolver();
    virtual ~LeastSquaresSolver();

    void setDataPoints(const QVector<double> &xData, const QVector<double> &yData);
    void solve();

    virtual double operator()(const double &x) const = 0;

protected:
    QVector<double> xData;
    QVector<double> yData;

    ceres::Problem *problem;

    virtual void prepareProblem() = 0;
};

#endif // LEASTSQUARESSOLVER_H
