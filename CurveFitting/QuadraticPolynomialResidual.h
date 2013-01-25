#ifndef QUADRATICPOLYNOMIALRESIDUAL_H
#define QUADRATICPOLYNOMIALRESIDUAL_H

// y = a*x^2 + b*x + c
class QuadraticPolynomialResidual
{
public:
    QuadraticPolynomialResidual(const double &x, const double &y);

    template <typename T> bool operator()(const T* const a, const T* const b, const T* const c, T* residual) const
    {
        residual[0] = T(y) - a[0] * T(x) * T(x) - b[0] * T(x) - c[0];

        return true;
    }

private:
    // the sample's observations
    const double x;
    const double y;
};

#endif // QUADRATICPOLYNOMIALRESIDUAL_H
