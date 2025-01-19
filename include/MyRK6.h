//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the sixth-order Runge-Kutta integrator
// Global error: O(h^6)
//

#ifndef MYRK6_H
#define MYRK6_H

#include "MyODEIntegrator.h"

class MyRK6 final : public MyODEIntegrator
{
public:
	MyRK6() = default;
	~MyRK6() override = default;

	void step(const double& t, const double& h, arma::Col<double>& x, MyFunctor& f) const override;
};

#endif //MYRK6_H
