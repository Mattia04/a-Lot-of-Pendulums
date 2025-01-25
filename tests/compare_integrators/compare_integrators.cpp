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
#include <cmath>

#include "MyDoublePendulum.hpp"
#include "ODE_Integrators/MyRKN.hpp"
#include "ODE_Integrators/MyDRKN.hpp"
#include "ODE_Integrators/MySODEIntegrator.hpp"

using namespace std;

int main() {
	cout << "Comparison started" << endl;

	// ~~~ physical problem
	auto Pendulum = MySimpleDoublePendulum();

	// ~~~ simulation parameters
	const vector<const double> step_sizes = {0.5, 0.1, 0.05, 0.01, 0.005, 0.001};
	constexpr double total_time = 10.; // s

	// ~~~ integrators
	const vector<MyODEIntegrator*> Integrators
		= {new MyRK4(), new MyRK5(), new MyRK6(), new MyRK7()};
	const vector<vector<MyDODEIntegrator*>> DIntegrators = {
		{
			new MyRKF45(1e-1, total_time, 1e-2),
			new MyRKF45(1e-2, total_time, 1e-3),
			new MyRKF45(1e-3, total_time, 1e-4)
		},
		{new MyRKDP45(1e-1, total_time, 1e-2)},
		{new MyRKDP45(1e-2, total_time, 1e-3)},
		{new MyRKDP45(1e-3, total_time, 1e-4)},
	};
	const vector<MySODEIntegrator*> SIntegrators = {new MyVer()};


	// ~~~~~ First comparison (RKN)
	cout << "First comparison" << endl;
	constexpr double t = 0.;
	for (int i = 0; i < Integrators.size(); i++)
	{
		for (int k = 0; k < step_sizes.size(); k++)
		{
			string file_name = "./../tests/compare_integrators/outRK" +
				to_string(i+4) + "_" + to_string(k) + ".txt";
			ofstream outputFile(file_name);
			if (!outputFile.is_open())
			{
				throw runtime_error("Could not open file " + file_name);
			}

			arma::Col coords {M_PI_2, M_PI_2, 0., 0.};
			arma::Col coordsT {M_PI_2, M_PI_2, 0., 0.};
			int steps = ceil(total_time / step_sizes[k]);
			for (int j = 0; j < steps; j++)
			{
				Integrators[i]->step(t, step_sizes[k], coords, Pendulum);

				Integrators[i]->step(t, step_sizes[k] * .5, coordsT, Pendulum);
				Integrators[i]->step(t, step_sizes[k] * .5, coordsT, Pendulum);

				arma::Col result = coordsT - coords;
				outputFile << result[0] << " " << result[1] << " " << result[2] << " " << result[3] << endl;
			}
			outputFile.close();
		}
	}

	// FUCK OFF DYNAMIC STEP INTEGRATORS
	// // ~~~~~ Second comparison (DRK)
	// cout << "Second comparison" << endl;
	// for (int i = 0; i < DIntegrators.size(); i++)
	// {
	// 	for (int j = 0; j < DIntegrators[i].size(); j++)
	// 	{
	// 		string file_name = "./../tests/compare_integrators/outDRK" +
	// 			to_string(i) + "_" + to_string(j) + ".txt";
	// 		ofstream outputFile(file_name);
	// 		if (!outputFile.is_open())
	// 		{
	// 			throw runtime_error("Could not open file " + file_name);
	// 		}
	//
	// 		arma::Col coords {M_PI_2, M_PI_2, 0., 0.};
	// 		while (DIntegrators[i][j]->GetTime() <= total_time)
	// 		{
	// 			DIntegrators[i][j]->step(coords, Pendulum);
	//
	// 			cout << DIntegrators[i][j]->GetTime() << "\b\r" << endl;
	//
	// 			outputFile << DIntegrators[i][j]->GetTime() << " " << DIntegrators[i][j]->GetError() << endl;
	// 		}
	// 		outputFile.close();
	// 	}
	// }

	// ~~~~~ Third comparison (symplectic)
	cout << "Third comparison" << endl;
	for (int i = 0; i < SIntegrators.size(); i++)
	{
		for (int k = 0; k < step_sizes.size(); k++)
		{
			string file_name = "./../tests/compare_integrators/outSRK" +
				to_string(i) + "_" + to_string(k) + ".txt";
			ofstream outputFile(file_name);
			if (!outputFile.is_open())
			{
				throw runtime_error("Could not open file " + file_name);
			}

			arma::Col QCoords {M_PI_2, M_PI_2};
			arma::Col PCoords {0., 0.};
			arma::Col QCoordsT {M_PI_2, M_PI_2};
			arma::Col PCoordsT {0., 0.};
			int steps = ceil(total_time / step_sizes[k]);
			for (int j = 0; j < steps; j++)
			{
				SIntegrators[i]->step(t, step_sizes[k], QCoords, PCoords, Pendulum);

				SIntegrators[i]->step(t, step_sizes[k] * .5, QCoordsT, PCoordsT, Pendulum);
				SIntegrators[i]->step(t, step_sizes[k] * .5, QCoordsT, PCoordsT, Pendulum);

				arma::Col result = join_cols(QCoordsT - QCoords, PCoordsT - PCoords);
				outputFile << result[0] << " " << result[1] << " " << result[2] << " " << result[3] << endl;
			}
			outputFile.close();
		}
	}

	cout << "Comparison completed" << endl;

	return 0;
}
