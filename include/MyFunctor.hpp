//
// Created by Mattia Ballico on 15/01/25.
//

#ifndef MYFUNCTOR_H
#define MYFUNCTOR_H

#include <armadillo>

class MyFunctor {
public:
	virtual ~MyFunctor() = default;

	[[nodiscard]] virtual arma::Col<double> eval(const arma::Col<double>  &x) const = 0;

	arma::Col<double> operator()(const arma::Col<double>  &x) const {return eval(x);}

	arma::Col<double> operator()(const arma::Col<double>& x, const arma::Col<double>& v) const
		{ return this->eval(join_cols(x, v)); }
};



#endif //MYFUNCTOR_H
