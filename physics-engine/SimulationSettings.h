#ifndef SIMULATION_SETTINGS_H
#define SIMULATION_SETTINGS_H

struct SimulationSettings {
	double TimeScale = 2000000.0;
	double SimulationTime = 0.0;

	bool paused = false;
	bool ResetRequested = false;
};


#endif // !SIMULATION_SETTINGS_H

