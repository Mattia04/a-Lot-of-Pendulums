//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the fifth-order Runge-Kutta integrator
// Global error: O(h^5)
//

#ifndef MYRK5_H
#define MYRK5_H

#include "MyODEIntegrator.h"

// Coefficients for the Butcher tableau
static constexpr float m_A[5] = {
	0.25, 0.375, 0.9230769230769231, 1.0, 0.5
}; // m_A is here just for future implementations with time dependence

static constexpr float m_B[5][5] = {
	{0.25},
	{0.09375, 0.28125},
	{0.8793809740555303, -3.277196176604461, 3.3208921256258535},
	{2.0324074074074074, -8.0, 7.173489278752436, -0.20589668615984405},
	{-0.2962962962962963, 2.0, -1.3816764132553607, 0.4529727095516569, -0.275}
};

static constexpr float m_C[6] = {
	0.11851851851851852, 0.0, 0.5189863547758284, 0.5061314903420167, -0.18, 0.03636363636363636
};

class MyRK5 final : public MyODEIntegrator
{
	public:
	MyRK5() = default;
	~MyRK5() override = default;

	void step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const override;
};


#endif //MYRK5_H
