//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the sixth-order Runge-Kutta integrator
// Global error: O(h^6)
//

#ifndef MYRK6_H
#define MYRK6_H

#include "MyODEIntegrator.h"

// Coefficients for the Butcher tableau for RK6
static constexpr float m_A[6] = {
	0.2, 0.3, 0.6, 1.0, 0.875, 1.0
}; // m_A is here just for future implementations with time dependence

static constexpr float m_B[6][6] = {
	{0.2},
	{0.075, 0.225},
	{0.3, -0.9, 1.2},
	{-0.2037037037037037, 2.5, -2.5925925925925926, 1.2962962962962963},
	{0.029296296296296294, -0.5128205128205128, 0.6756756756756757, 0.5925925925925926, 0.125},
	{0.09788359788359788, 0.0, 0.4025764895330113, 0.21043771043771043, -0.0883545757976266, 0.37745768474558475}
};

static constexpr float m_C[7] = {
	0.1, 0.0, 0.29999999999999993, 0.44, 0.34, 0.25, 0.0625
};

class MyRK6 final : public MyODEIntegrator
{
public:
	MyRK6() = default;
	~MyRK6() override = default;

	void step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const override;
};

#endif //MYRK6_H
