#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
	constexpr double G = 6.67430e-11;
	namespace Astronomy {
		constexpr double AU = 1.495978707e11;
	}
	namespace Rendering {
		constexpr double DistanceScale = Astronomy::AU / 50.0;
		constexpr double RadiusScale = Astronomy::AU/50.0;
		constexpr double Timescale = 2000000.0;
		constexpr double VisualExaggeration = 500.0;
	}
	namespace Sun {
		constexpr double Mass = 1.98847e30;
		constexpr double Radius = 6.963e8;
	}
	namespace Mercury {
		constexpr double Mass = 3.3011e23;
		constexpr double Radius = 2.4397e6;
		constexpr double Distance = 0.387 * Astronomy::AU;
		constexpr double OrbitalSpeed = 47870.0;
	}
	namespace Venus {
		constexpr double Mass = 4.8675e24;
		constexpr double Radius = 6.0519e6;
		constexpr double Distance = 0.723 * Astronomy::AU;
		constexpr double OrbitalSpeed = 35020.0;
	}
	namespace Earth {
		constexpr double Mass = 5.9722e24;
		constexpr double Radius = 6.371e6;
		constexpr double Distance = Astronomy::AU;
		constexpr double OrbitalSpeed = 29780.0;
	}
	namespace Moon {
		constexpr double Mass = 7.342e22;
		constexpr double Radius = 1.737e6;
		constexpr double Distance = 3.844e8;
		constexpr double OrbitalSpeed = 1022.0;
	}
	namespace Mars {
		constexpr double Mass = 6.417e23;
		constexpr double Radius = 3.389e6;
		constexpr double Distance = 1.524 * Astronomy::AU;
		constexpr double OrbitalSpeed = 24070.0;
	}
	namespace Jupiter
	{
		constexpr double Mass = 1.8982e27;
		constexpr double Radius = 6.9911e7;
		constexpr double Distance = 5.204 * Astronomy::AU;
		constexpr double OrbitalSpeed = 13070.0;
	}
	namespace Saturn {
		constexpr double Mass = 5.6834e26;
		constexpr double Radius = 5.8232e7;
		constexpr double Distance = 9.582 * Astronomy::AU;
		constexpr double OrbitalSpeed = 9680.0;
	}
	namespace Uranus
	{
		constexpr double Mass = 8.6810e25;
		constexpr double Radius = 2.5362e7;
		constexpr double Distance = 19.191 * Astronomy::AU;
		constexpr double OrbitalSpeed = 6800.0;
	}
	namespace Neptune
	{
		constexpr double Mass = 1.02413e26;
		constexpr double Radius = 2.4622e7;
		constexpr double Distance = 30.07 * Astronomy::AU;
		constexpr double OrbitalSpeed = 5430.0;
	}
}

#endif // !CONSTANTS_H

