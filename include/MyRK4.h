//
// Created by Mattia Ballico on 15/01/25.
//

#ifndef MYRK4_H
#define MYRK4_H

#include "MyODEIntegrator.h"

class MyRK4 final : public MyODEIntegrator {
public:
	MyRK4() = default;
	~MyRK4() override = default;

	arma::Col<float> step(const float &h,
							const arma::Col<float> &x,
							MyFunctor &f) const override
	{
		const arma::Col k1 = f(x);
		const arma::Col k2 = f(x + h / 2 * k1);
		const arma::Col k3 = f(x + h / 2 * k2);
		const arma::Col k4 = f(x + h * k3);

		return x + h/6*(k1 + 2*k2 + 2*k3 + k4);
	};
};



#endif //MYRK4_H
