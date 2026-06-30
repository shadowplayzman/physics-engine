#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
	constexpr double G = 6.67430e-11;
	namespace Astronomy {
		constexpr double AU = 1.495978707e11;
		constexpr double SolarMass = 1.98847e30;
		constexpr double EarthMass = 5.9722e24;
		constexpr double EarthOrbitalSpeed = 29780.0;
	}
	namespace Rendering {
		constexpr double RenderScale = Astronomy::AU / 50.0;
		constexpr double Timescale = 846000.0;

	}
}

#endif // !CONSTANTS_H

