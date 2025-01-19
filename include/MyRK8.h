//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the eighth-order Runge-Kutta integrator
// Global error: O(h^8)
//

#ifndef MYRK8_H
#define MYRK8_H

#include "MyODEIntegrator.h"

class MyRK8 final : public MyODEIntegrator
{
public:
	MyRK8() = default;
	~MyRK8() override = default;

	void step(const double& t, const double& h, arma::Col<double>& x, MyFunctor& f) const override;
};

#endif //MYRK8_H
