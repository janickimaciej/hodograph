#pragma once

#include <glm/glm.hpp>

#include <chrono>
#include <random>
#include <vector>

class Simulation
{
public:
	enum class FunctionType
	{
		none,
		constant,
		step,
		stepPeriodic,
		sinus
	};

	void update();
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
	float getX() const;
	float getAlpha() const;
	const float* getTVector() const;
	const float* getXVector() const;
	const float* getVVector() const;
	const float* getAVector() const;

private:
	bool m_running = false;

	float m_alpha{};
	float m_dt = 0.01f;
	float m_r = 1.0f;
	float m_l = 3.0f;
	float m_omega = glm::radians(90.0f);
	float m_stdDev = 0.01f;
	bool m_disturbance = false;

	std::random_device m_randomDevice{};
	std::mt19937 m_randomGenerator{m_randomDevice()};

	std::chrono::time_point<std::chrono::system_clock> m_t0{};
	std::vector<float> m_t{};
	std::vector<float> m_x{};
	std::vector<float> m_v{};
	std::vector<float> m_a{};

	float getTime() const;
	void resetTime();
};
