//
// Created by Mattia Ballico on 15/01/25.
//
// Code for the classic Runge-Kutta integrator
// Global error: O(h^4)
//

#ifndef MYRK4_H
#define MYRK4_H

#include "MyODEIntegrator.h"

class MyRK4 final : public MyODEIntegrator {
public:
	MyRK4() = default;
	~MyRK4() override = default;

	void step(const double &t, const double &h,
							arma::Col<double> &x,
							MyFunctor &f) const override
	{
		const arma::Col<double> k1 = f(x);
		const arma::Col<double> k2 = f(x + h / 2 * k1);
		const arma::Col<double> k3 = f(x + h / 2 * k2);
		const arma::Col<double> k4 = f(x + h * k3);

		x += h/6*(k1 + 2*k2 + 2*k3 + k4);
	};
};



#endif //MYRK4_H
