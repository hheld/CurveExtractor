/*  CurveExtractor A simple tool to extract data points from images.
 *  Copyright (c) 2013, Harald Held <harald.held@gmail.com>
 *  All rights reserved.
 *  https://bitbucket.org/hheld/curveextractor
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *  (1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *
 *  (3) The name of the author may not be used to
 *      endorse or promote products derived from this software without
 *      specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

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
    virtual QString toString() const = 0;

protected:
    QVector<double> xData;
    QVector<double> yData;

    ceres::Problem *problem;

    virtual void prepareProblem() = 0;
};

#endif // LEASTSQUARESSOLVER_H
