#include "simulation.hpp"

#include <cmath>

void Simulation::update()
{
	if (!m_running)
	{
		return;
	}

	float frameT = getTime();
	int iterations = static_cast<int>(frameT / m_dt);

	while (m_t.size() <= iterations)
	{
		float t = m_t.size() * m_dt;
		m_alpha += m_omega * m_dt;

		float l = m_l;
		if (m_disturbance)
		{
			std::normal_distribution<float> distribution{0, m_stdDev};
			l += distribution(m_randomGenerator);
		}

		float x = m_r * std::cos(m_alpha) +
			std::sqrt(l * l - m_r * m_r * std::sin(m_alpha) * std::sin(m_alpha));

		m_t.push_back(t);
		m_x.push_back(x);

		if (getIterations() >= 3)
		{
			float prevX = m_x[m_x.size() - 3];
			float currX = m_x[m_x.size() - 2];
			float nextX = m_x[m_x.size() - 1];
			m_v.push_back((nextX - prevX) / (2.0f * m_dt));
			m_a.push_back((nextX - 2.0f * currX + prevX) / (m_dt * m_dt));

			if (getIterations() == 3)
			{
				m_v[0] = m_v.back();
				m_v[1] = m_v.back();
				m_a[0] = m_a.back();
				m_a[1] = m_a.back();
			}
		}
		else
		{
			m_v.push_back(0);
			m_a.push_back(0);
		}
	}
}

void Simulation::stop()
{
	m_running = false;
}

void Simulation::start()
{
	if (m_running)
	{
		return;
	}

	m_alpha = 0.0f;

	m_t.clear();
	m_x.clear();
	m_v.clear();
	m_a.clear();

	m_t.push_back(0);
	m_x.push_back(m_r + m_l);
	m_v.push_back(0);
	m_a.push_back(0);

	resetTime();
	m_running = true;
}

float Simulation::getDT() const
{
	return m_dt;
}

void Simulation::setDT(float dt)
{
	if (m_running)
	{
		return;
	}

	m_dt = dt;
}

float Simulation::getR() const
{
	return m_r;
}

void Simulation::setR(float r)
{
	m_r = r;
}

float Simulation::getL() const
{
	return m_l;
}

void Simulation::setL(float l)
{
	m_l = l;
}

float Simulation::getOmega() const
{
	return m_omega;
}

void Simulation::setOmega(float omega)
{
	m_omega = omega;
}

float Simulation::getStdDev() const
{
	return m_stdDev;
}

void Simulation::setStdDev(float stdDev)
{
	m_stdDev = stdDev;
}

bool Simulation::getDisturbance() const
{
	return m_disturbance;
}

void Simulation::setDisturbance(bool disturbance)
{
	m_disturbance = disturbance;
}

int Simulation::getIterations() const
{
	return static_cast<int>(m_t.size());
}

float Simulation::getT() const
{
	if (m_t.empty())
	{
		return 0;
	}
	return m_t.back();
}

float Simulation::getX() const
{
	if (m_x.empty())
	{
		return m_r + m_l;
	}
	return m_x.back();
}

float Simulation::getAlpha() const
{
	return m_alpha;
}

const float* Simulation::getTVector() const
{
	return m_t.data();
}

const float* Simulation::getXVector() const
{
	return m_x.data();
}

const float* Simulation::getVVector() const
{
	return m_v.data();
}

const float* Simulation::getAVector() const
{
	return m_a.data();
}

float Simulation::getTime() const
{
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
	std::chrono::duration<float> deltaT = t - m_t0;
	return deltaT.count();
}

void Simulation::resetTime()
{
	m_t0 = std::chrono::system_clock::now();
}
