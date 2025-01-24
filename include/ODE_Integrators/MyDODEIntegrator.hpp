//
// Created by Mattia Ballico on 20/01/25.
//
// This class has the same purpose of `MyODEIntegrator` but it is not the same.
// This class is an abstract class for dynamic step integrators such as
// MyRKF45 and MyRKDP45. (The "D" in `MyDODEIntegrator` stands for Dynamic)
//


#ifndef MYDODEINTEGRATOR_H
#define MYDODEINTEGRATOR_H

#include "MyFunctor.hpp"

class MyDODEIntegrator {
public:
	explicit MyDODEIntegrator(const double &h, const double &t_max, const double &tolerance)
		: m_h(h), m_t_tot(t_max), m_tol(tolerance) {};
	virtual ~MyDODEIntegrator() = default;

	virtual void step(arma::Col<double> &x, MyFunctor &f) = 0;

	virtual void ChangeStepSize()
	{
		if (m_err == 0)
			throw std::runtime_error("Error in MyDODEIntegrator::ChangeStepSize: error is zero, make sure to update the error before changing step_size");

		m_h *= std::max(0.5, std::min(2., 0.95 * std::pow(m_tol / m_err,0.2)));
	};

	[[nodiscard]] double GetTime()  const { return m_t; };
	[[nodiscard]] double GetError() const { return m_err; };

protected:
	double m_h;
	double m_t = 0;
	double m_t_tot;
	double m_tol; // tolerance
	double m_err = 0; // error of last step
};

#endif //MYDODEINTEGRATOR_H
