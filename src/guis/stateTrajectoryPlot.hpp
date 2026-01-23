#pragma once

#include "scene.hpp"

#include <glm/glm.hpp>

class StateTrajectoryPlot
{
public:
	StateTrajectoryPlot(const Scene& scene, const glm::vec2& pos, const glm::vec2& size,
		const bool& autoFitPlots);
	void update();

private:
	const Scene& m_scene;
	const glm::vec2 m_pos;
	const glm::vec2 m_size;
	const bool& m_autoFitPlots;
};
