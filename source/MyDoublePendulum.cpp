//
// Created by Mattia Ballico on 15/01/25.
//

#include "MyDoublePendulum.h"

std::vector<float> MySimpleDoublePendulum::eval(const std::vector<float>& x) const
{
    const float cos_d = std::cos(x[0]-x[1]);
    const float sin_d = std::sin(x[0]-x[1]);
    const float den = 2 - cos_d*cos_d;
    const float den2 = den*den;
    const float prod = x[2]*x[3];
    const float num = cos_d*sin_d*(x[2]*x[2] + 2*x[3]*x[3] + 2*prod);

    return std::vector{
        (x[2] - x[3]*cos_d)/den,
        (2*x[3] - x[2]*cos_d)/den,
        static_cast<float>(num / den2 + prod * sin_d / den - 2*M_G *std::sin(x[0])),
        static_cast<float>(num / den2 - prod * sin_d / den - 2*M_G *std::sin(x[1]))
    };
}
