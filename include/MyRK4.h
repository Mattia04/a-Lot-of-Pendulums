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

	std::vector<float> step(const float &h,
							const std::vector<float> &x,
							std::function<std::vector<float>(std::vector<float>)> &f) const override
	{
		arma::vec<float> k1 = f(x);
		std::vector<float> k2 = f(x + h / 2 * k1);
		std::vector<float> k3 = f(x + h / 2 * k2);
		std::vector<float> k4 = f(x + h * k3);

		return x + h/6*(k1 + 2*k2 + 2*k3 + k4);
	};
};



#endif //MYRK4_H
