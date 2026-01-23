#pragma once

#include "scene.hpp"

#include <glm/glm.hpp>

#include <functional>
#include <string>

class TimePlot
{
public:
	using DataGetter = std::function<const float*(void)>;
	TimePlot(const Scene& scene, const DataGetter& dataGetter, const glm::vec2& pos,
		const glm::vec2& size, const std::string& windowLabel, const std::string& plotName,
		const bool& autoFitPlots);
	void update();

private:
	const Scene& m_scene;
	DataGetter m_dataGetter{};
	const glm::vec2 m_pos{};
	const glm::vec2 m_size{};
	const std::string m_windowLabel{};
	const std::string m_plotName{};
	const bool& m_autoFitPlots;
};
