//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the Runge–Kutta–Fehlberg integrator
// Global error: O(h^5) but with error estimate: O(h^4)
//

#ifndef MYRKF45_H
#define MYRKF45_H

#include "MyDODEIntegrator.h"

class MyRKF45 final : public MyDODEIntegrator {
public:
	MyRKF45(const double h, const double t_max, const double tolerance)
		: MyDODEIntegrator(h, t_max, tolerance) {};
	~MyRKF45() override = default;

	void step(arma::Col<double> &x, MyFunctor &f) override;
};

#endif //MYRKF45_H
