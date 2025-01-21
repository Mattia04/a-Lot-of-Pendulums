//
// Created by Mattia Ballico on 17/01/25.
//
// NOTE: this code does not work anymore, I keep it just for reference.
//
// To use: replace this code in the main.cpp file and compile as usual.
// Then it will create a file: outputFile.txt which contains the angles
// and angluar velocities for an example, here is already given an example.
//

#include <iostream>
#include <fstream>
#include <CL/opencl.h>

#include "MyDoublePendulum.h"
#include "MyRK4.h"

#define FPS 60

using namespace std;

int main() {
	cout << "Test started" << endl;
	ofstream outputFile("./../outputFile.txt");

	const MyODEIntegrator *Integrator = new MyRK4();
	auto Pendulum = MySimpleDoublePendulum();

	constexpr float step_size = 1./FPS;
	constexpr float total_time = 10; // s
	constexpr int steps = total_time * FPS;
	arma::Col<float> coords {M_PI_2, M_PI_2, 0, 0};

	for (int i = 0; i < steps; i++)
	{
		coords = Integrator->step(step_size, coords, Pendulum);
		outputFile << coords[0] << " " << coords[1] << " " << coords[2] << " " << coords[3] << endl;
	}

	return 0;
}