//
// Created by Mattia Ballico on 15/01/25.
//

#ifndef MYFUNCTOR_H
#define MYFUNCTOR_H

#include <armadillo>

class MyFunctor {
public:
	virtual ~MyFunctor() = default;

	[[nodiscard]] virtual arma::Col<float> eval(const arma::Col<float>  &x) const = 0;

	arma::Col<float>  operator()(const arma::Col<float>  &x) const {return eval(x);}
};



#endif //MYFUNCTOR_H
