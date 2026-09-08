#ifndef SAND_BOX_MANAGER
#define SAND_BOX_MANAGER
#include"CelestialBody.h"
enum class AppMode {
	SolarSystem,
	SandBox
};
enum class SandBoxType {
	None,Gravity,
	PrijectileMotion,
	Collison
};

class SandBoxManager {
	private:
		AppMode appmode;
		SandBoxType activeSandbox;
		CelestialBody* environment;
	public:
		SandBoxManager();
		void SetEnvironment(CelestialBody* body);
		CelestialBody* GetEnvironment() const;
		void EnterSandbox(SandBoxType type);
		void ExitSandbox();
		AppMode GetAppMode() const;
		SandBoxType GetActiveSandbox() const;


};

#endif // !SAND_BOX_MANAGER
