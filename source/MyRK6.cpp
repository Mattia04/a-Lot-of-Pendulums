//
// Created by Mattia Ballico on 19/01/25.
//

#include "MyRK6.h"

namespace
{
	// Coefficients for the Butcher tableau for RK6
	constexpr double m_A[6] = {
		1./3, 2./3, 1./3, 1./2, 1./2, 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr double m_B[6][6] = {
		{1./3},
		{0, 2./3},
		{1./12, 1./3, -1./12},
		{-1./16, 9./8, -3./16, -3./8},
		{0, 9./8, -3./8, -3./4, 1./2},
		{9./44, -9./11, 63./44, 18./11, 0, -16./11}
	};

	constexpr double m_C[7] = {
		11./120, 0, 27./40, 27./40, -4./15, -4./15, 11./120
	};
}

void MyRK6::step(const double& t, const double& h, arma::Col<double>& x, MyFunctor& f) const {
	arma::Col<double> k[7];

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