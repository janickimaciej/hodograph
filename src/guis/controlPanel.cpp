#include "guis/controlPanel.hpp"

#include <imgui/imgui.h>

#include <algorithm>

ControlPanel::ControlPanel(Scene& scene, const glm::vec2& pos, const glm::vec2& size,
	bool& autoFitPlots) :
	m_scene{scene},
	m_pos{pos},
	m_size{size},
	m_autoFitPlots{autoFitPlots}
{ }

void ControlPanel::update()
{
	ImGui::SetNextWindowPos({m_pos.x, m_pos.y}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({m_size.x, m_size.y}, ImGuiCond_Always);
	ImGui::Begin("controlPanel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	if (ImGui::Button("Start"))
	{
		m_scene.start();
	}

	ImGui::Spacing();

	if (ImGui::Button("Stop"))
	{
		m_scene.stop();
	}

	ImGui::Spacing();

	ImGui::Text("t = %.2f", m_scene.getT());

	separator();

	updateValue
	(
		[this] () { return m_scene.getDT(); },
		[this] (float dt) { m_scene.setDT(dt); },
		"dt",
		0.001f,
		"%.3f"
	);

	updateValue
	(
		[this] () { return m_scene.getR(); },
		[this] (float r) { m_scene.setR(r); },
		"r",
		0.1f
	);

	updateValue
	(
		[this] () { return m_scene.getL(); },
		[this] (float l) { m_scene.setL(l); },
		"l",
		0.1f
	);

	updateValue
	(
		[this] () { return m_scene.getOmega(); },
		[this] (float omega) { m_scene.setOmega(omega); },
		"omega",
		0.1f
	);

	separator();

	ImGui::Checkbox("Auto fit plots", &m_autoFitPlots);

	ImGui::End();
}

void ControlPanel::updateValue(const std::function<float()>& get,
	const std::function<void(float)>& set, const std::string& name, std::optional<float> min,
	const std::string& format)
{
	static const std::string suffix = "##controlPanel";
	static constexpr float stepPrecision = 0.1f;

	ImGui::PushItemWidth(100);

	float value = get();
	float prevValue = value;
	ImGui::InputFloat((name + suffix).c_str(), &value, stepPrecision, stepPrecision,
		format.c_str());
	if (min.has_value())
	{
		value = std::max(value, *min);
	}
	if (value != prevValue)
	{
		set(value);
	}

	ImGui::PopItemWidth();
}

void ControlPanel::separator()
{
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
}
