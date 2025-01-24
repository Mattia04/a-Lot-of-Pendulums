//
// Created by Mattia Ballico on 21/01/25.
//

#include "ODE_Integrators/MyDRKN.hpp"

// ============ DRK methods as derived classes ============
namespace m_RKF45
{
	// Coefficients for the Butcher tableau for RK6
	constexpr double m_A[5] = {
		1./2, 1./2, 1., 2./3, 1./5
	}; // m_A is here just for future implementations with time dependence

	constexpr double m_B[5][5] = {
		{1./2},
		{1./4, 1./4},
		{0, -1., 2.},
		{7./27, 10./27, 0, 1./27},
		{28./625, -1./5, 546./625, 54./625, -378./625},
	};

	constexpr double m_CH[6] = {
		1./24, 0, 0, 5./48, 27./56, 125./336
	};

	constexpr double m_CT[6] = {
		1./8, 0, 2./3, 1./16, -27./56, -125./336
	};
}
MyRKF45::MyRKF45(const double &h, const double &t_max, const double &tolerance) : MyDRKN(m_RKF45::m_A, m_RKF45::m_B, m_RKF45::m_CH,
m_RKF45::m_CT, h, t_max, tolerance) {}


namespace m_RKDP45
{
	// Coefficients for the Butcher tableau for RK6
	constexpr double m_A[6] = {
		1./5, 3./10, 4./5, 8./9, 1., 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr double m_B[6][6] = {
		{1./5},
		{3./40, 9./40},
		{44./45, -56./15, 32./9},
		{19372./6561, -25360./2187, 64448./6561, -212./729},
		{9017./3168, -355./33, 46732./5247, 49./176, -5103./18656},
		{35./384, 0, 500./1113, 125./192, -2187./6784, 11./84},
	};

	constexpr double m_CH[7] = {
		35./384, 0, 500./1113, 125./192, -2187./6784, 11./84, 0
	};

	constexpr double m_CT[7] = {
		5179./57600, 0, 757./16695, 393./640, -92097./339200, 187./2100, 1./40
	}; // todo check if the CT are the correct ones or if i have e to subtract CH to them
}
MyRKDP45::MyRKDP45(const double &h, const double &t_max, const double
&tolerance) : MyDRKN(m_RKDP45::m_A, m_RKDP45::m_B, m_RKDP45::m_CH, m_RKDP45::m_CT, h, t_max, tolerance) {}