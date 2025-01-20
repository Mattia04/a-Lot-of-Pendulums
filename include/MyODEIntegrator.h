//
// Created by Mattia Ballico on 15/01/25.
//

#ifndef ODEINTEGRATOR_H
#define ODEINTEGRATOR_H

#include "MyFunctor.h"

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
