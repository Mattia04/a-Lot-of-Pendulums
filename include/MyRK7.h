//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the seventh-order Runge-Kutta integrator
// Global error: O(h^8)
//

#ifndef MYRK7_H
#define MYRK7_H

#include "MyODEIntegrator.h"

class MyRK7 final : public MyODEIntegrator
{
public:
	MyRK7() = default;
	~MyRK7() override = default;

	void step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const override;
};

#endif //MYRK7_H
