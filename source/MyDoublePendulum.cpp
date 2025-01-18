//
// Created by Mattia Ballico on 15/01/25.
//

#include "MyDoublePendulum.h"

arma::Col<float>  MySimpleDoublePendulum::eval(const arma::Col<float> &x) const
{
    const float cos_d = std::cos(x[0]-x[1]);
    const float sin_d = std::sin(x[0]-x[1]);
    const float den = 2 - cos_d*cos_d;
    const float den2 = den*den;
    const float prod = x[2]*x[3];
    const float num = sin_d*( (x[2]*x[2] + 2*x[3]*x[3])*cos_d - prod*(2+cos_d*cos_d));
    const float f1 = cos_d / den;
    const float f2 = num / den2;

    return arma::Col {
        (-   x[2] + x[3]) * f1,
        (- 2*x[3] + x[2]) * f1,
        static_cast<float>(- f2 + 2*M_G *std::sin(x[0])),
        static_cast<float>(  f2 +   M_G *std::sin(x[1]))
    };
}
