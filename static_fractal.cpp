#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include <omp.h>

#include "include/MyDoublePendulum.hpp"
#include "include/ODE_Integrators/MyRKN.hpp"

using namespace std;

int main()
{
	cout << "Test started" << endl;

	constexpr int PIXELS = 128;
	constexpr double step_size = 1e-3;
	constexpr double total_time = 50; // s
	const int steps = ceil(total_time / step_size);
	constexpr double DTheta = 2 * M_PI / PIXELS;

	// Preallocate results matrix
	vector<vector<double>> results(PIXELS / 2,
								   vector<double>(
									   PIXELS, total_time + step_size));

	const auto start_clock = chrono::high_resolution_clock::now();

	// Shared progress counter
	const int total_pixels = (PIXELS / 2) * PIXELS;
	int completed_pixels = 0;

	// Configure CPU throttling (delay in milliseconds)
	constexpr int delay_ms = 10;

	#pragma omp parallel for collapse(2) shared(completed_pixels) // Parallelize both loops
	for (int i = 0; i < PIXELS / 2; i++)
	{
		for (int j = 0; j < PIXELS; j++)
		{
			const auto* Integrator = new MyRK4();
			auto Pendulum = MySimpleDoublePendulum();

			arma::Col<double> coords{
				(i + 0.5) * DTheta - M_PI,
				(j + 0.5) * DTheta - M_PI,
				0,
				0
			};

			// Skip invalid initial conditions
			if (2 * cos(coords[0]) + cos(coords[1]) > 1)
			{
				delete Integrator;
				#pragma omp atomic
				completed_pixels++;
				continue;
			}

			// Progress reporting every 0.39% of total work
			if (completed_pixels % (total_pixels / 256) == 0)
			{
				#pragma omp critical
				{
					const auto now = chrono::high_resolution_clock::now();
					const double elapsed = chrono::duration<double>(now - start_clock).count();
					const double progress = static_cast<double>(completed_pixels) / total_pixels;
					const double estimated = (progress > 0) ? (elapsed / progress - elapsed) : 0;

					cout << "\b\rProgress: "
						 << 100 * progress << "% | Elapsed: "
						 << elapsed << "s | Remaining: "
						 << estimated << "s" << flush;
				}
			}

			double t = 0;
			for (int k = 0; k < steps; k++)
			{
				Integrator->step(t, step_size, coords, Pendulum);
				t += step_size;

				if (abs(coords[0] - coords[1]) >= 2 * M_PI)
				{
					results[i][j] = t;
					break;
				}
			}
			// Add a small delay to reduce CPU load
			this_thread::sleep_for(chrono::milliseconds(delay_ms));

			delete Integrator;

			// Update progress counter
			#pragma omp atomic
			completed_pixels++;
		}
	}

	// Write results to file
	ofstream outputFile("./../tests/static_fractal/output.csv");
	for (const auto& row : results)
	{
		for (size_t j = 0; j < row.size(); ++j)
		{
			outputFile << row[j] << (j + 1 < row.size() ? ", " : "\n");
		}
	}

	cout << "\nTotal time: "
		 << chrono::duration<double>(
			 chrono::high_resolution_clock::now() - start_clock).count()
		 << "s" << endl;

	return 0;
}
