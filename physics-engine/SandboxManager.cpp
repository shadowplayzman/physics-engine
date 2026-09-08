#include "SandBoxManager.h"
SandBoxManager::SandBoxManager() {
	appmode = AppMode::SolarSystem;
	activeSandbox = SandBoxType::None;
	environment = nullptr;
}
void SandBoxManager::SetEnvironment(CelestialBody* body) {
	environment = body;

}
CelestialBody* SandBoxManager::GetEnvironment() const {
	return environment;
}
void SandBoxManager::EnterSandbox(SandBoxType type) {
	activeSandbox = type;
	appmode = AppMode::SandBox;

}
void SandBoxManager::ExitSandbox() {
	activeSandbox = SandBoxType::None;
	appmode = AppMode::SolarSystem;
}
AppMode SandBoxManager::GetAppMode() const {
	return appmode;
}
SandBoxType SandBoxManager::GetActiveSandbox() const {
	return activeSandbox;
}