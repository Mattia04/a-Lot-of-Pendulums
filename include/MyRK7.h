//
// Created by Mattia Ballico on 19/01/25.
//
// Code for the seventh-order Runge-Kutta integrator
// Global error: O(h^8)
//

#ifndef MYRK7_H
#define MYRK7_H

#include "MyODEIntegrator.h"

// Coefficients for the Butcher tableau for RK7
static constexpr float m_A[7] = {
	0.14285714285714285, 0.2857142857142857, 0.42857142857142855, 0.7142857142857143, 0.8571428571428571, 1.0, 1.0
}; // m_A is here just for future implementations with time dependence

static constexpr float m_B[7][7] = {
	{0.14285714285714285},
	{0.07142857142857142, 0.21428571428571427},
	{0.125, -0.375, 0.6785714285714286},
	{0.2, -0.6285714285714286, 1.2571428571428571, -0.08571428571428572},
	{-0.125, 0.24285714285714285, 0.24285714285714285, -0.6571428571428571, 0.6714285714285714},
	{0.022857142857142857, -0.2, 0.34285714285714286, 0.08571428571428572, -0.05714285714285714, 0.20714285714285716},
	{0.10204166666666666, 0.0, 0.3833333333333333, 0.24479166666666666, -0.0625, 0.16979166666666666, 0.1625}
};

static constexpr float m_C[8] = {
	0.10204166666666666, 0.0, 0.3833333333333333, 0.24479166666666666, -0.0625, 0.16979166666666666, 0.1625, 0.0
};

class MyRK7 final : public MyODEIntegrator
{
public:
	MyRK7() = default;
	~MyRK7() override = default;

	void step(const float& t, const float& h, arma::Col<float>& x, MyFunctor& f) const override;
};

#endif //MYRK7_H
