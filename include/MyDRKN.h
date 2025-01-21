//
// Created by Mattia Ballico on 21/01/25.
//
// Code for a generalized Runge-Kutta solver (with variable step size)
// `MyDRKN` is an abstract class so the child classes need just the butcher
// table and the number of steps, this is to not repeat code.

#ifndef MYDRKN_H
#define MYDRKN_H

#include "MyDODEIntegrator.h"

template <unsigned int N> // number of steps of the method
class MyDRKN : public MyDODEIntegrator {
public:
	/*
	 * todo add comment
	 */
	MyDRKN(const double a[N], const double b[N][N], const double ch[N+1], const double ct[N+1], const double &h, const double &t_max, const double &tolerance):
		MyDODEIntegrator(h, t_max, tolerance), m_A(), m_B(), m_CH(), m_CT()
	{
		std::copy(a, a + N, m_A);
		for (int i = 0; i < N; ++i)
		{
			std::copy(b[i], b[i] + N, m_B[i]);
		}
		std::copy(ch, ch + N + 1, m_CH);
		std::copy(ct, ct + N + 1, m_CT);
	}

	void step(arma::Col<double>& x, MyFunctor& f) override
	{
		if (m_t + m_h > m_t_tot) // check to not overshoot max time
			m_h = m_t_tot - m_t;

		arma::Col<double> x_f;
		do {
			// compute RK steps
			arma::Col<double> k[N];

			k[0] = m_h * f(x);
			for (int i = 1; i < N; i++) {
				auto temp = x;
				for (int j = 0; j < i; j++) {
					temp += m_B[i-1][j] * k[j];
				}
				k[i] = m_h * f(temp);
			}

			// compute result
			arma::Col<double> x_err = x;
			x_f = x;
			for (int i = 0; i < N; i++) {
				x_err += m_CT[i] * k[i]; // error estimate
				x_f += m_CH[i] * k[i]; // next step
			}

			m_err = max(abs(x_err));
			if (m_err < m_tol / 4. or m_err > m_tol)
				ChangeStepSize();
		} while (m_err > m_tol); // re-do step if error is too big

		m_t += m_h;
		x = x_f;
	}

private:
	double m_A[N];
	double m_B[N][N];
	double m_CH[N + 1];
	double m_CT[N + 1];
};

// ============ RK methods as derived classes ============
class MyRKF45 final : public MyDRKN<5> {
public:
	MyRKF45(const double &h, const double &t_max, const double &tolerance);
};

class MyRKDP45 final : public MyDRKN<6> {
public:
	MyRKDP45(const double &h, const double &t_max, const double &tolerance);
};

#endif //MYDRKN_H
