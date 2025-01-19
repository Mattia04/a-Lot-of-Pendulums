//
// Created by Mattia Ballico on 19/01/25.
//

#include "MyRK5.h"

// Coefficients for the Butcher tableau
namespace
{
	constexpr float m_A[5] = {
		1./4, 1./4, 1./2, 3./4, 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr float m_B[5][5] = {
		{0.25},
		{1./8, 1./8},
		{0, -1./2, 1},
		{3./16, 0, 0, 9./16},
		{-3./7, 2./7, 12./7, -12./7, 8./7}
	};

	constexpr float m_C[6] = {
		7./90, 0, 32./90, 12./90, 32./90, 7./90
	};
}

void MyRK5::step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const {
	arma::Col<float> k[6];

	k[0] = h * f(x);
    for (int i = 1; i < 6; i++) {
        auto temp = x;
    	for (int j = 0; j < i; j++) {
        	temp += m_B[i-1][j] * k[j];
    	}
        k[i] = h * f(temp);
    }

    for (int i = 0; i < 6; i++) {
    	x += m_C[i] * k[i];
    }
}