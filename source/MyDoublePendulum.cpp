//
// Created by Mattia Ballico on 15/01/25.
//

#include "MyDoublePendulum.h"

arma::Col<double>  MySimpleDoublePendulum::eval(const arma::Col<double> &x) const
{
    const double cos_d = std::cos(x[0]-x[1]);
    const double sin_d = std::sin(x[0]-x[1]);
    const double den = 2 - cos_d*cos_d;
    const double den2 = den*den;
    const double prod = x[2]*x[3];
    const double num = sin_d*( (x[2]*x[2] + 2*x[3]*x[3])*cos_d - prod*(2+cos_d*cos_d));
    const double f2 = num / den2;

    return arma::Col {
        (-   x[2] + x[3]*cos_d) /den,
        (- 2*x[3] + x[2]*cos_d) /den,
        - f2 + 2*M_G *std::sin(x[0]),
          f2 +   M_G *std::sin(x[1])
    };
}
