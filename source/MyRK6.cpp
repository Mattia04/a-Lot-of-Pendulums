//
// Created by Mattia Ballico on 19/01/25.
//

#include "MyRK6.h"

void MyRK6::step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const {
	arma::Col<float> k[7];

	k[0] = h * f(x);
	for (int i = 1; i < 7; i++) {
		auto temp = x;
		for (int j = 0; j < i; j++) {
			temp += m_B[i-1][j] * k[j];
		}
		k[i] = h * f(temp);
	}

	for (int i = 0; i < 7; i++) {
		x += m_C[i] * k[i];
	}
}