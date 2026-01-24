#include "scene.hpp"

#include "mesh.hpp"

#include <glad/glad.h>
#include <glm/gtc/constants.hpp>

#include <vector>

static constexpr float fovYDeg = 60.0f;
static constexpr float nearPlane = 0.1f;
static constexpr float farPlane = 1000.0f;

static constexpr float ceilingThickness = 0.2f;
static constexpr float ceilingSize = 3;
static constexpr float springFreeLength = 5;
static constexpr float springThickness = 0.1f;
static constexpr float weightSize = 1;

Scene::Scene(const glm::ivec2& viewportSize) :
	m_viewportSize{viewportSize}
{
	m_circle = std::make_unique<Mesh>(std::vector<glm::vec2>{});
	updateCircle();
	m_connection = std::make_unique<Mesh>(std::vector<glm::vec2>{});
	updateConnection();
	m_block = std::make_unique<Mesh>(std::vector<glm::vec2>{});
	updateBlock();
	m_xAxis = std::make_unique<Mesh>(std::vector<glm::vec2>{});
	updateXAxis();
	m_yAxis = std::make_unique<Mesh>(std::vector<glm::vec2>{});
	updateYAxis();

	updateCamera();
}

void Scene::update()
{
	m_simulation.update();

	updateConnection();
	updateBlock();
}

void Scene::render() const
{
	static constexpr glm::vec3 backgroundColor{0.1f, 0.1f, 0.1f};
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaderProgram.use();
	m_shaderProgram.setUniform("minPos", m_minPos);
	m_shaderProgram.setUniform("maxPos", m_maxPos);

	m_circle->render();
	m_connection->render();
	m_block->render();
	m_xAxis->render();
	m_yAxis->render();
}

void Scene::stop()
{
	m_simulation.stop();
}

void Scene::start()
{
	m_simulation.start();
}

float Scene::getDT() const
{
	return m_simulation.getDT();
}

void Scene::setDT(float dt)
{
	m_simulation.setDT(dt);
}

float Scene::getR() const
{
	return m_simulation.getR();
}

void Scene::setR(float r)
{
	m_simulation.setR(r);

	updateCircle();
	updateConnection();
	updateBlock();
	updateXAxis();
	updateYAxis();

	updateCamera();
}

float Scene::getL() const
{
	return m_simulation.getL();
}

void Scene::setL(float l)
{
	m_simulation.setL(l);

	updateConnection();
	updateBlock();
	updateXAxis();

	updateCamera();
}

float Scene::getOmega() const
{
	return m_simulation.getOmega();
}

void Scene::setOmega(float omega)
{
	m_simulation.setOmega(omega);
}

float Scene::getStdDev() const
{
	return m_simulation.getStdDev();
}

void Scene::setStdDev(float stdDev)
{
	m_simulation.setStdDev(stdDev);
}

bool Scene::getDisturbance() const
{
	return m_simulation.getDisturbance();
}

void Scene::setDisturbance(bool disturbance)
{
	m_simulation.setDisturbance(disturbance);
}

int Scene::getIterations() const
{
	return m_simulation.getIterations();
}

float Scene::getT() const
{
	return m_simulation.getT();
}

const float* Scene::getTVector() const
{
	return m_simulation.getTVector();
}

const float* Scene::getXVector() const
{
	return m_simulation.getXVector();
}

const float* Scene::getVVector() const
{
	return m_simulation.getVVector();
}

const float* Scene::getAVector() const
{
	return m_simulation.getAVector();
}

void Scene::updateCircle()
{
	std::vector<glm::vec2> vertices{};

	static constexpr float vertexCount = 200;
	static constexpr float dAlpha = 2 * glm::pi<float>() / vertexCount;
	float r = m_simulation.getR();
	for (int i = 0; i < vertexCount; ++i)
	{
		vertices.push_back({r * std::cos(i * dAlpha), r * std::sin(i * dAlpha)});
	}
	vertices.push_back({r, 0});

	m_circle->update(vertices);
}

void Scene::updateConnection()
{
	std::vector<glm::vec2> vertices{};

	float r = m_simulation.getR();
	float alpha = m_simulation.getAlpha();
	vertices.push_back({0, 0});
	vertices.push_back({r * std::cos(alpha), r * std::sin(alpha)});
	vertices.push_back({m_simulation.getX(), 0});

	m_connection->update(vertices);
}

void Scene::updateBlock()
{
	std::vector<glm::vec2> vertices{};

	static constexpr float blockLength = 0.1f;
	float x = m_simulation.getX();
	vertices.push_back({x - blockLength / 2.0f, -blockLength / 2.0f});
	vertices.push_back({x + blockLength / 2.0f, -blockLength / 2.0f});
	vertices.push_back({x + blockLength / 2.0f, blockLength / 2.0f});
	vertices.push_back({x - blockLength / 2.0f, blockLength / 2.0f});
	vertices.push_back({x - blockLength / 2.0f, -blockLength / 2.0f});

	m_block->update(vertices);
}

void Scene::updateXAxis()
{
	std::vector<glm::vec2> vertices{};
	
	static constexpr float margin = 1.1f;
	float r = m_simulation.getR();
	float l = m_simulation.getL();
	vertices.push_back({-margin * r, 0});
	vertices.push_back({margin * r + l, 0});

	m_xAxis->update(vertices);
}

void Scene::updateYAxis()
{
	std::vector<glm::vec2> vertices{};
	
	static constexpr float margin = 1.1f;
	float r = m_simulation.getR();
	vertices.push_back({0, -margin * r});
	vertices.push_back({0, margin * r});

	m_yAxis->update(vertices);
}

void Scene::updateCamera()
{
	static constexpr float margin = 1.5f;
	float r = m_simulation.getR();
	float l = m_simulation.getL();
	m_minPos = {-margin * r, -margin * r};
	m_maxPos = {margin * r + l, margin * r};

	float dX = m_maxPos.x - m_minPos.x;
	float dY = m_maxPos.y - m_minPos.y;
	float aspectRatio = dX / dY;
	float viewportAspectRatio = static_cast<float>(m_viewportSize.y) / m_viewportSize.x;

	if (aspectRatio > viewportAspectRatio)
	{
		float newDY = dX / viewportAspectRatio;
		float offset = newDY - dY;
		m_minPos.y -= offset / 2.0f;
		m_maxPos.y += offset / 2.0f;
	}
	else
	{
		float newDX = dY * viewportAspectRatio;
		float offset = newDX - dX;
		m_minPos.x -= offset / 2.0f;
		m_maxPos.x += offset / 2.0f;
	}
}
