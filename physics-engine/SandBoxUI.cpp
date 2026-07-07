#include"SandBoxUI.h"
#include"CelestialBody.h"
#include"Constants.h"
#include"SimulationSettings.h"
#include"SimulationState.h"
#include"IMGUI/imgui.h"
#include<algorithm>
bool preserveDensity=true;

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


void SandBoxUI::DrawSimulationWindow(SimulationSettings& settings, SimulationState& simulationState, Universe& universe, Camera& camera) {
    CelestialBody* body = camera.GetTargetBody();
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

    if (body != nullptr) {
        ImGui::Text("Target: %s", body->Name.c_str());
    }

    ImGui::Separator();
    ImGui::Text("FPS %.1f", ImGui::GetIO().Framerate);
    DrawSimulationTime(settings.SimulationTime);

    ImGui::End();


}
void SandBoxUI::DrawPlanetWindow(SimulationSettings& settings, SimulationState& simulationState, Universe& universe, Camera& camera) {
    CelestialBody* body = camera.GetTargetBody();
    double radiusPercentage = (body->radius / body->originalRadius) * 100;
    double massPercentage = (body->mass / body->originalMass) * 100;
    double min = 1.0;
    double max = 500.0;


    ImGui::Begin("Planet Inspector");

    if (body != nullptr) {
        ImGui::Text("Name: %s", body->Name.c_str());
        ImGui::Separator();
        ImGui::Checkbox("Preserve Density", &preserveDensity);
        ImGui::SameLine();
        ImGui::TextDisabled("(?)");
        if (ImGui::IsAnyItemHovered()) {
            ImGui::SetTooltip("When enabled, changing the radius automatically\n"
                "updates the mass to keep density constant.");
        }

        ImGui::SliderScalar("Radius", ImGuiDataType_Double, &radiusPercentage, &min, &max, "%.0f%%");
        body->SetRadiusPercentage(radiusPercentage, preserveDensity);
        ImGui::Text("Actual Radius: %.2e m", body->radius);
        if (preserveDensity) {
            ImGui::Text("Actual Mass: %.3e kg ", body->mass);
        }
        else
        {
            ImGui::SliderScalar("Mass", ImGuiDataType_Double, &massPercentage, &min, &max,"%.0f%%");
            body->SetMassPercentage(massPercentage);
            ImGui::Text("Actual Mass: %.3e kg ", body->mass);
        }
        ImGui::Separator();
        ImGui::Text("Rendering");
        if (body->Name == "Sun") {
            ImGui::Text("Distance from Sun: 0.00 AU");

        }
        else {
            double distance = glm::length(body->transform.position);
            double distanceInAU = distance / Constants::Astronomy::AU;
            ImGui::Text("Distance from Sun: %.3f AU", distanceInAU);
        }


        ImGui::Separator();
        ImGui::Text("Velocity");
        ImGui::Text("X: %.2f m/s", body->velocity.x);
        ImGui::Text("Y: %.2f m/s", body->velocity.y);
        ImGui::Text("Z: %.2f m/s", body->velocity.z);
        
        glm::dvec3 velocity = body->velocity;
        ImGui::InputDouble("Velocity X", &velocity.x);
        ImGui::InputDouble("Velocity Y", &velocity.y);
        ImGui::InputDouble("Velocity Z", &velocity.z);
        body->SetVelocity(velocity);

        ImGui::Separator();
        ImGui::Text("Position");
        ImGui::Text("X: %.2e m", body->transform.position.x);
        ImGui::Text("Y: %.2e m", body->transform.position.y);
        ImGui::Text("Z: %.2e m", body->transform.position.z);
        ImGui::Separator();
        ImGui::Text("Trails");
        ImGui::InputInt("Trail Length", &body->trailSettings.displayedPoints);
        body->trailSettings.displayedPoints = std::clamp(body->trailSettings.displayedPoints, 1, 5000);
        ImGui::Text("Trail Points: %d", body->trail.size());
        ImGui::Separator();
        ImGui::ColorEdit3("Trail Color", &body->trailSettings.color.x);
    }
    else {
        ImGui::Text("No Planet Selected");
    }

    ImGui::End();

}