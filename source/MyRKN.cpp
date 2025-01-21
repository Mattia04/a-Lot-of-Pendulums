//
// Created by Mattia Ballico on 20/01/25.
//

#include "MyRKN.h"

// ============ RK methods as derived classes ============
namespace m_RK4
{
	constexpr double m_A[3] = {
		1./2, 1./2, 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr double m_B[3][3] = {
		{1./2},
		{0, 1./2},
		{0, 0, 1.},
	};

	constexpr double m_C[4] = {
		1./6, 1./3, 1./3, 1./6
	};
}
MyRK4::MyRK4() : MyRKN(m_RK4::m_A, m_RK4::m_B, m_RK4::m_C) {}

namespace m_RK5
{
	constexpr double m_A[5] = {
		1./4, 1./4, 1./2, 3./4, 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr double m_B[5][5] = {
		{0.25},
		{1./8, 1./8},
		{0, -1./2, 1},
		{3./16, 0, 0, 9./16},
		{-3./7, 2./7, 12./7, -12./7, 8./7}
	};

	constexpr double m_C[6] = {
		7./90, 0, 32./90, 12./90, 32./90, 7./90
	};
}
MyRK5::MyRK5() : MyRKN(m_RK5::m_A, m_RK5::m_B, m_RK5::m_C) {}


namespace m_RK6
{
	constexpr double m_A[6] = {
		1./3, 2./3, 1./3, 1./2, 1./2, 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr double m_B[6][6] = {
		{1./3},
		{0, 2./3},
		{1./12, 1./3, -1./12},
		{-1./16, 9./8, -3./16, -3./8},
		{0, 9./8, -3./8, -3./4, 1./2},
		{9./44, -9./11, 63./44, 18./11, 0, -16./11}
	};

	constexpr double m_C[7] = {
		11./120, 0, 27./40, 27./40, -4./15, -4./15, 11./120
	};
}
MyRK6::MyRK6() : MyRKN(m_RK6::m_A, m_RK6::m_B, m_RK6::m_C) {}


namespace m_RK7
{
	// Coefficients for the Butcher tableau for RK7
	constexpr double m_A[8] = {
		1./6, 1./3, 1./2, 2./11, 2./3, 6./7, 0, 1.
	}; // m_A is here just for future implementations with time dependence

	constexpr double b8 = 77./1440;
	constexpr double m_B[8][8] = {
		{1./6},
		{0, 1./3},
		{1./8, 0, 3./8},
		{148./1331, 0, 150./1331, -56./1331},
		{-404./243, 0, -170./27, 4024./1701, 10648./1701},
		{2466./2401, 0, 1242./343, -19176./16807, -51909./16807, 1053./2401},
		{1. / (576*b8), 0, 0, 1./(105*b8), -1331./(279552*b8), -9./(1024*b8), 343./(149760+b8)},
		{-71. / 32 - b8 * 270./11, 0, -195./22, 32./7, 29403./3584, -729./512, 1029./1408, b8 * 270./11}
	};

	constexpr double m_C[9] = {
		77./1440 - b8, 0, 0, 32./105, 1771561./6289920, 243./2560, 16807./74880, b8, 11./270};
}
MyRK7::MyRK7() : MyRKN(m_RK7::m_A, m_RK7::m_B, m_RK7::m_C) {}
