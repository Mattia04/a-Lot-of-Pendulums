#include <iostream>
#include <fstream>
#include <CL/opencl.h>

#include "MyDoublePendulum.hpp"
#include "MyRK8.h"

#define FPS 60

using namespace std;

int main() {
	cout << "Test started" << endl;
	ofstream outputFile("./../outputFile.txt");

	const auto *Integrator = new MyRK8();
	auto Pendulum = MySimpleDoublePendulum();

	constexpr double step_size = 1./FPS;
	constexpr double total_time = 10; // s
	constexpr int steps = total_time * FPS;
	arma::Col<double> coords {M_PI_2, M_PI_2, 0, 0};
	double t = 0;

	for (int i = 0; i < steps; i++)
	{
		Integrator->step(t, step_size, coords, Pendulum);
		outputFile << coords[0] << " " << coords[1] << " " << coords[2] << " " << coords[3] << endl;
		t += step_size;
	}

	return 0;
}