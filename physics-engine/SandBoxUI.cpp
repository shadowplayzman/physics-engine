#include"SandBoxUI.h"
#include"SimulationSettings.h"
#include"IMGUI/imgui.h"
void SandBoxUI::Draw(SimulationSettings& settings) {
    ImGui::Begin("Physics Engine");

    ImGui::Separator();

    ImGui::Text("Simulation!");

    double min = 0.0;
    double max = 5000000.0;

    ImGui::SliderScalar("Time Scale",ImGuiDataType_Double, &settings.TimeScale, &min, &max);

    ImGui::Text("FPS %.1f", ImGui::GetIO().Framerate);

    ImGui::End();
}