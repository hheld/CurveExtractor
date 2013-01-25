#ifndef LEASTSQUARESSOLVER_H
#define LEASTSQUARESSOLVER_H

#include <QVector>

/**
 * The LeastSquaresSolver class fits a quadratic polynomial y=a*x^2+b*x+c to given measurement data pairs (x,y).
 */
class LeastSquaresSolver
{
public:
    LeastSquaresSolver();

    void setDataPoints(const QVector<double> &xData, const QVector<double> &yData);
    void solve();

    /**
     * @return y, with y = a*x^2+b*x+c
     */
    double operator()(const double &x) const;

private:
    QVector<double> xData;
    QVector<double> yData;

    // the parameters to be fitted
    double a;
    double b;
    double c;
};

#endif // LEASTSQUARESSOLVER_H
