//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the eighth-order Runge-Kutta integrator
// Global error: O(h^8)
//

#ifndef MYRK8_H
#define MYRK8_H

#include "MyODEIntegrator.h"

// Coefficients for the Butcher tableau for RK8
static constexpr float m_A[8] = {
	0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1.0
}; // m_A is here just for future implementations with time dependence

static constexpr float m_B[8][8] = {
	{0.125},
	{0.041666666666666664, 0.20833333333333334},
	{0.020833333333333332, -0.08333333333333333, 0.4375},
	{0.03125, -0.15625, 0.375, 0.25},
	{-0.046875, 0.234375, -0.15625, 0.328125, 0.265625},
	{0.01953125, -0.09765625, 0.08203125, 0.4296875, -0.14453125, 0.41015625},
	{-0.016927083333333332, 0.08463541666666667, -0.0625, 0.32421875, 0.11197916666666667, -0.22265625, 0.4817708333333333},
	{0.025, 0.0, 0.2, 0.16666666666666666, -0.125, 0.075, 0.43333333333333335, 0.225}
};

static constexpr float m_C[9] = {
	0.041666666666666664, 0.0, 0.16666666666666666, 0.20833333333333334, -0.125, 0.25, 0.225, 0.23333333333333334, 0.0
};

class MyRK8 final : public MyODEIntegrator
{
public:
	MyRK8() = default;
	~MyRK8() override = default;

	void step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const override;
};

#endif //MYRK8_H
