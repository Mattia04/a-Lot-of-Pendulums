//
// Created by Mattia Ballico on 15/01/25.
//

#ifndef MYDOUBLEPENDULUM_H
#define MYDOUBLEPENDULUM_H

#include "MyDoublePendulum.hpp"
#include "MyFunctor.hpp"

#define M_G 9.806

class MySimpleDoublePendulum final : public MyFunctor {
	/*
	 * Simple double pendulum with lengths of 1, masses of 1 and gravitational
	 * acceleration equal to M_G to keep the numer of operations low.
	 */
	public:
		MySimpleDoublePendulum() = default;
		~MySimpleDoublePendulum() override = default;

		[[nodiscard]] arma::Col<double> eval(const arma::Col<double>  &x) const override;
};



#endif //MYDOUBLEPENDULUM_H
