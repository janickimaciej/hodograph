#include "guis/timePlot.hpp"

#include <imgui/imgui.h>
#include <implot/implot.h>

TimePlot::TimePlot(const Scene& scene, const DataGetter& dataGetter, const glm::vec2& pos,
	const glm::vec2& size, const std::string& windowLabel, const std::string& plotName,
	const bool& autoFitPlots) :
	m_scene{scene},
	m_dataGetter{dataGetter},
	m_pos{pos},
	m_size{size},
	m_windowLabel{windowLabel},
	m_plotName{plotName},
	m_autoFitPlots{autoFitPlots}
{ }

void TimePlot::update()
{
	static constexpr int offset = 17;

	ImGui::SetNextWindowPos({m_pos.x, m_pos.y}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({m_size.x, m_size.y}, ImGuiCond_Always);
	ImGui::Begin(m_windowLabel.c_str(), nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	static constexpr float xAxisRange = 15;
	ImPlot::SetNextAxisLimits(ImAxis_X1, std::max(m_scene.getT() - xAxisRange, 0.0f),
		std::max(m_scene.getT(), xAxisRange), ImPlotCond_Always);
	if (ImPlot::BeginPlot(m_plotName.c_str(), {m_size.x - offset, m_size.y - offset}))
	{
		ImPlot::SetupAxes("", "", 0, m_autoFitPlots ? ImPlotAxisFlags_AutoFit : 0);
		ImPlot::PlotLine("", m_scene.getTVector(), m_dataGetter(), m_scene.getIterations());
		ImPlot::EndPlot();
	}

	ImGui::End();
}
