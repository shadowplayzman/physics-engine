#include"SandBoxUI.h"
#include"CelestialBody.h"
#include"SimulationSettings.h"
#include"SimulationState.h"
#include"IMGUI/imgui.h"

static void DrawSimulationTime(double seconds) {
    const int SecondsPerMinute = 60;
    const int SecondsPerHour = 60 * SecondsPerMinute;
    const int SecondsPerDay = 24 * SecondsPerHour;
    const int SecondsPerYear = static_cast<int>(365.25 * SecondsPerDay);

    int years = static_cast<int>(seconds / SecondsPerYear);
    seconds -= years * SecondsPerYear;

    int days = static_cast<int>(seconds / SecondsPerDay);
    seconds -= days * SecondsPerDay;

    int hours = static_cast<int>(seconds / SecondsPerHour);
    seconds -= hours * SecondsPerHour;

    int minutes = static_cast<int>(seconds / SecondsPerMinute);

    ImGui::Text("Simulation TIme");

    ImGui::Text("%d Years", years);
    ImGui::Text("%d Days", days);
    ImGui::Text("%d Hours", hours);
    ImGui::Text("%d Minutes", minutes);
}


void SandBoxUI::Draw(SimulationSettings& settings, SimulationState& simulationState, Universe& universe, Camera& camera) {
    ImGui::Begin("Physics Engine");

    ImGui::Separator();

    ImGui::Text("Simulation!");

    double min = 0.0;
    double max = 5000000.0;

    ImGui::SliderScalar("Time Scale",ImGuiDataType_Double, &settings.TimeScale, &min, &max);

    ImGui::Checkbox("Pause Simulation", &settings.paused);
    if (simulationState !=SimulationState::CameraTranstion) {
         if (ImGui::Button("Reset Solar System")) {
             settings.ResetRequested = true;
         }

    }

    ImGui::Separator();

    ImGui::Text("Status");

    const char* stateString = "";

    switch (simulationState) {
        case SimulationState::Running:
            stateString = "Running";
            break;
        case SimulationState::CameraTranstion:
            stateString = "Camera Transition";
            break;
    }

    ImGui::Text("State: %s", stateString);

    ImGui::Text("Bodies:%d", universe.BodyCount());

    if (camera.GetTargetBody() != nullptr) {
        ImGui::Text("Target: %s", camera.GetTargetBody()->Name.c_str());
    }

    ImGui::Separator();
    ImGui::Text("FPS %.1f", ImGui::GetIO().Framerate);
    DrawSimulationTime(settings.SimulationTime);

    ImGui::End();
}