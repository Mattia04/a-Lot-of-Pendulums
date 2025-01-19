//
// Created by Mattia Ballico on 19/01/25.
//

#include "MyRK7.h"

void MyRK7::step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const {
	arma::Col<float> k[8];

	k[0] = h * f(x);
	for (int i = 1; i < 8; i++) {
		auto temp = x;
		for (int j = 0; j < i; j++) {
			temp += m_B[i-1][j] * k[j];
		}
		k[i] = h * f(temp);
	}

	for (int i = 0; i < 8; i++) {
		x += m_C[i] * k[i];
	}
}