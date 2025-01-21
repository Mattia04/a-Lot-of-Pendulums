//
// Created by Mattia Ballico on 20/01/25.
//
// Code for a generalized Runge-Kutta solver (with fixed step size)
// `MyRKN` is an abstract class so the child classes need just the butcher
// table and the number of steps, this is to not repeat code.

#ifndef MYRKN_H
#define MYRKN_H

#include "MyODEIntegrator.h"

template <unsigned int N> // number of steps of the method
class MyRKN : public MyODEIntegrator {
public:
	/*
	 * todo add comment
	 */
	MyRKN(const double a[N], const double b[N][N], const double c[N+1]):
	m_A(), m_B(), m_C()
	{
		std::copy(a, a + N, m_A);
		for (int i = 0; i < N; ++i) {
			std::copy(b[i], b[i] + N, m_B[i]);
		}
		std::copy(c, c + N + 1, m_C);
	}

	void step(const double& t, const double& h, arma::Col<double>& x, MyFunctor& f) const override
	{
		arma::Col<double> k[N + 1];
		k[0] = h * f(x);

		for (int i = 1; i <= N; ++i) {
			auto temp = x;

			for (int j = 0; j < i; ++j)
				temp += m_B[i - 1][j] * k[j];

			k[i] = h * f(temp);
		}

		for (int i = 0; i <= N; ++i)
			x += m_C[i] * k[i];
	}

private:
	double m_A[N];
	double m_B[N][N];
	double m_C[N + 1];

};

// ============ RK methods as derived classes ============
class MyRK4 final : public MyRKN<3> {
public:
	MyRK4();
};

class MyRK5 final : public MyRKN<5> {
public:
	MyRK5();
};

class MyRK6 final : public MyRKN<6> {
public:
	MyRK6();
};

class MyRK7 final : public MyRKN<8> {
public:
	MyRK7();
};


#endif //MYRKN_H
