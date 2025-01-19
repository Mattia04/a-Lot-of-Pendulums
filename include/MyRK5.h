//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the fifth-order Runge-Kutta integrator
// Global error: O(h^5)
//

#ifndef MYRK5_H
#define MYRK5_H

#include "MyODEIntegrator.h"

class MyRK5 final : public MyODEIntegrator
{
	public:
	MyRK5() = default;
	~MyRK5() override = default;

	void step(const double& t, const double& h, arma::Col<double>& x, MyFunctor& f) const override;
};


#endif //MYRK5_H
