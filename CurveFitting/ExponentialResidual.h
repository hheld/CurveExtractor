#ifndef EXPONENTIALRESIDUAL_H
#define EXPONENTIALRESIDUAL_H

#include <cmath>

// y = a*exp(b*x^2+c)
class ExponentialResidual
{
public:
    ExponentialResidual(const double &x, const double &y);

    template <typename T> bool operator()(const T* const a, const T* const b, const T* const c, T* residual) const
    {
        residual[0] = T(y) - a[0] * exp(b[0]*T(x) * T(x) + c[0]);

        return true;
    }

private:
    // the sample's observations
    const double x;
    const double y;
};

#endif // EXPONENTIALRESIDUAL_H
