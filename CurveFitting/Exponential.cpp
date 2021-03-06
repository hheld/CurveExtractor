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

#include <QString>

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

QString Exponential::toString() const
{
    QString str("%1*exp(%2x^2+%3)");

    return str.arg(a).arg(b).arg(c);
}
