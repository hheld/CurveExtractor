#ifndef CUBICPOLYNOMIALRESIDUAL_H
#define CUBICPOLYNOMIALRESIDUAL_H

// y = a*x^3 + b*x^2 + c*x + d
class CubicPolynomialResidual
{
public:
    CubicPolynomialResidual(const double &x, const double &y);

    template <typename T> bool operator()(const T* const a, const T* const b, const T* const c, const T* const d, T* residual) const
    {
        residual[0] = T(y) - a[0] * T(x) * T(x) * T(x) - b[0] * T(x) * T(x) - c[0] * T(x) - d[0];

        return true;
    }

private:
    // the sample's observations
    const double x;
    const double y;
};

#endif // CUBICPOLYNOMIALRESIDUAL_H
