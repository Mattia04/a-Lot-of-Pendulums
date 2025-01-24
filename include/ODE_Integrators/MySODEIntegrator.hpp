//
// Created by Mattia Ballico on 23/01/25.
//
// This class has the same purpose of `MyODEIntegrator` but it is not the same.
// This class is an abstract class for *Symplectic integrators* ssuch as
// Verlet. (The "S" in `MyDODEIntegrator` stands for Symplectic)
//

#ifndef MYSODEINTEGRATOR_H
#define MYSODEINTEGRATOR_H

#include "MyFunctor.hpp"

class MySODEIntegrator {
public:
	MySODEIntegrator() = default;
	virtual ~MySODEIntegrator() = default;

	virtual void step(const double &t,
		const double &h,
		arma::Col<double> &x,
		arma::Col<double> &v,
		MyFunctor &f)
	= 0;
};

// Verlet's method
class MyVer final : public MySODEIntegrator
{
public:
	MyVer() = default;
	~MyVer() override = default;

	void step(const double &t, const double& h, arma::Col<double> &x, arma::Col<double> &v, MyFunctor &f) override
	{
		const unsigned int N = x.n_elem;
		auto t1 = f(x, v);
		v += t1.tail(N);
		auto t2 = f(x, v);
		x += t2.head(N);
		auto t3 = f(x, v);
		v += t3.tail(N);
	}
};

// I could add Beeman's algorithm [[https://en.wikipedia.org/wiki/Beeman%27s_algorithm]]
// I could add Leapfrog [[https://en.wikipedia.org/wiki/Leapfrog_integration]]

#endif //MYSODEINTEGRATOR_H
