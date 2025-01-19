//
// Created by Mattia Ballico on 19/01/25.
//

#include "MyRK5.h"

void MyRK5::step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const {
	arma::Col<float> k[6];

	k[0] = h * f(x);
    for (int i = 1; i < 5; i++) {
        auto temp = x;
    	for (int j = 0; j < i; j++) {
        	temp += m_B[i][j] * k[j];
    	}
        k[i] = h * f(temp);
    }

    for (int i = 0; i < 6; i++) {
    	x += m_C[i] * k[i];
    }
}