//
// Created by Mattia Ballico on 15/01/25.
//
// This is an abstract class for constant step size integrators such as:
// `MyRK4`, `MyRK5`, `MyRK6`, `MyRK7`, `MyRK8`.
//

#ifndef ODEINTEGRATOR_H
#define ODEINTEGRATOR_H

#include "MyFunctor.hpp"

class MyODEIntegrator {
public:
	MyODEIntegrator() = default;
  	virtual ~MyODEIntegrator() = default;

    virtual void step(const double &t,
    				const double &h,
                    arma::Col<double> &x,
                    MyFunctor &f)
		const = 0;
};

#endif //ODEINTEGRATOR_H
