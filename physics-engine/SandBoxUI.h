#ifndef SANDBOX_UI_H
#define SANDBOX_UI_H

#include"SimulationSettings.h"
#include"SimulationState.h"
#include"Universe.h"
#include"mesh.h"
#include"Camera.h"
class SandBoxUI {
	public:
		void DrawSimulationWindow(SimulationSettings& settings,
			SimulationState& simualtionState,
			Universe& universe,
			Camera& camera);
		void DrawPlanetWindow(SimulationSettings& settings,
			SimulationState& simualtionState,
			Universe& universe,
			Camera& camera);
		void DrawPlanetSpawner(
			SimulationSettings& settings,
			SimulationState& state,
			Universe& universe,
			Camera& camera,
			Mesh& sphereMesh);

};

#endif // !SANDBOX_UI_H

