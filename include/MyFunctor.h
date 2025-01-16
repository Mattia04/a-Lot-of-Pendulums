//
// Created by Mattia Ballico on 15/01/25.
//

#ifndef MYFUNCTOR_H
#define MYFUNCTOR_H

#include <armadillo>

class MyFunctor {
public:
	virtual ~MyFunctor() = default;

	[[nodiscard]] virtual std::vector<float> eval(const std::vector<float> &x) const = 0;

	std::vector<float> operator()(const std::vector<float> &x) const {return eval(x);}
};



#endif //MYFUNCTOR_H
