//
// Created by Mattia Ballico on 19/01/25.
//
// This code should make a comparison of the integrators to then analyse
// using a python script, the comparison are on the level step_size/error
// and step_size/time
//

#include <string>
#include <iostream>
#include <fstream>
#include <CL/opencl.h>

#include "MyDoublePendulum.h"
#include "MyRK4.h"
#include "MyRK5.h"
#include "MyRK6.h"
#include "MyRK7.h"
#include "MyRK8.h"

#define FPS 240

using namespace std;

int main() {
	cout << "Comparison started" << endl;

	const vector<MyODEIntegrator*> Integrators
		= {new MyRK4(), new MyRK5(), new MyRK6()};
	auto Pendulum = MySimpleDoublePendulum();

	constexpr double step_size = 1./FPS;
	constexpr double step_size_2 = step_size / 2.;
	constexpr double total_time = 20; // s
	constexpr int steps = total_time * FPS;

	for (int i = 0; i < Integrators.size(); i++)
	{
		string file_name = "./../tests/compare_integrators/outputRK" + to_string(i+4) + ".txt";
		ofstream outputFile(file_name);
		if (!outputFile.is_open())
		{
			throw runtime_error("Could not open file " + file_name);
		}
		arma::Col<double> coords {M_PI_2, M_PI_2, 0, 0};
		arma::Col<double> coordsT {M_PI_2, M_PI_2, 0, 0};
		for (int step = 0; step < steps; step++)
		{
			double t = 0;
			Integrators[i]->step(t, step_size, coords, Pendulum);

			Integrators[i]->step(t, step_size_2, coordsT, Pendulum);
			Integrators[i]->step(t, step_size_2, coordsT, Pendulum);

			const auto result = coordsT - coords;
			outputFile << result[0] << " " << result[1] << " " << result[2] << " " << result[3] << endl;
		}
		outputFile.close();
	}

	return 0;
}
