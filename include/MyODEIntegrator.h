//
// Created by Mattia Ballico on 15/01/25.
//

#ifndef ODEINTEGRATOR_H
#define ODEINTEGRATOR_H

#include <armadillo>
#include <functional>

class MyODEIntegrator {
public:
	MyODEIntegrator() = default;
  	virtual ~MyODEIntegrator() = default;

    virtual std::vector<float> step(const float &h,
                    const std::vector<float> &x,
                    std::function<std::vector<float>(std::vector<float>)> &f)
		const = 0;
};



#endif //ODEINTEGRATOR_H
