#pragma once

#include "mesh.hpp"
#include "simulation.hpp"

#include <glm/glm.hpp>

#include <memory>

class Scene
{
public:
	Scene(const glm::ivec2& viewportSize);
	void update();
	void render() const;

	void stop();
	void start();
	
	float getDT() const;
	void setDT(float dt);
	float getR() const;
	void setR(float r);
	float getL() const;
	void setL(float l);
	float getOmega() const;
	void setOmega(float omega);
	float getStdDev() const;
	void setStdDev(float stdDev);
	bool getDisturbance() const;
	void setDisturbance(bool disturbance);

	int getIterations() const;
	float getT() const;
	const float* getTVector() const;
	const float* getXVector() const;
	const float* getVVector() const;
	const float* getAVector() const;

private:
	glm::ivec2 m_viewportSize{};

	std::unique_ptr<Mesh> m_circle;
	std::unique_ptr<Mesh> m_connection;
	std::unique_ptr<Mesh> m_block;
	std::unique_ptr<Mesh> m_xAxis;
	std::unique_ptr<Mesh> m_yAxis;

	Simulation m_simulation{};

	glm::vec2 m_minPos{};
	glm::vec2 m_maxPos{};

	void updateCircle();
	void updateConnection();
	void updateBlock();
	void updateXAxis();
	void updateYAxis();

	void updateCamera();
};
