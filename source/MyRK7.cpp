//
// Created by Mattia Ballico on 19/01/25.
//

#include "MyRK7.h"

namespace
{
	// Coefficients for the Butcher tableau for RK7
	constexpr double m_A[8] = {
		1./6, 1./3, 1./2, 2./11, 2./3, 6./7, 0, 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr double b8 = 77./1440;
	constexpr double m_B[8][8] = {
		{1./6},
		{0, 1./3},
		{1./8, 0, 3./8},
		{148./1331, 0, 150./1331, -56./1331},
		{-404./243, 0, -170./27, 4024./1701, 10648./1701},
		{2466./2401, 0, 1242./343, -19176./16807, -51909./16807, 1053./2401},
		{1. / (576*b8), 0, 0, 1./(105*b8), -1331./(279552*b8), -9./(1024*b8), 343./(149760+b8)},
		{-71. / 32 - b8 * 270./11, 0, -195./22, 32./7, 29403./3584, -729./512, 1029./1408, b8 * 270./11}
	};

	constexpr double m_C[9] = {
		77./1440 - b8, 0, 0, 32./105, 1771561./6289920, 243./2560, 16807./74880, b8, 11./270};
}

void MyRK7::step(const double& t, const double& h, arma::Col<double>& x, MyFunctor& f) const {
	arma::Col<double> k[9];

	k[0] = h * f(x);
	for (int i = 1; i < 9; i++) {
		auto temp = x;
		for (int j = 0; j < i; j++) {
			temp += m_B[i-1][j] * k[j];
		}
		k[i] = h * f(temp);
	}

	for (int i = 0; i < 9; i++) {
		x += m_C[i] * k[i];
	}
}