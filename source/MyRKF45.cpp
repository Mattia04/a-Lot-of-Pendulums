//
// Created by Mattia Ballico on 20/01/25.
//

#include "MyRKF45.h"

namespace
{
	// Coefficients for the Butcher tableau for RK6
	constexpr double m_A[5] = {
		1./2, 1./2, 1., 2./3, 1./5
	}; // m_A is here just for future implementations with time dependence

	constexpr double m_B[5][5] = {
		{1./2},
		{1./4, 1./4},
		{0, -1., 2.},
		{7./27, 10./27, 0, 1./27},
		{28./625, -1./5, 546./625, 54./625, -378./625},
	};

	constexpr double m_CH[6] = {
		1./24, 0, 0, 5./48, 27./56, 125./336
	};

	constexpr double m_CT[6] = {
		1./8, 0, 2./3, 1./16, -27./56, -125./336
	};
}

void MyRKF45::step(arma::Col<double>& x, MyFunctor& f) {
	if (m_t + m_h > m_t_tot) // check to not overshoot max time
		m_h = m_t_tot - m_t;

	arma::Col<double> x5;
	do {
		// compute RK steps
		arma::Col<double> k[5];

		k[0] = m_h * f(x);
		for (int i = 1; i < 5; i++) {
			auto temp = x;
			for (int j = 0; j < i; j++) {
				temp += m_B[i-1][j] * k[j];
			}
			k[i] = m_h * f(temp);
		}

		// compute result
		arma::Col<double> x4 = x;
		x5 = x;
		for (int i = 0; i < 5; i++) {
			x4 += m_CT[i] * k[i]; // error estimate
			x5 += m_CH[i] * k[i]; // next step
		}

		m_err = max(abs(x4));
		if (m_err < m_tol / 4. or m_err > m_tol)
			ChangeStepSize();
	} while (m_err > m_tol); // re-do step if error is too big

	m_t += m_h;
	x = x5;
}
