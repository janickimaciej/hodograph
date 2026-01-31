#pragma once

#include "guis/gui.hpp"
#include "scene.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window();
	~Window();

	void init(Scene& scene);
	bool shouldClose() const;
	void swapBuffers() const;
	void pollEvents() const;

	glm::ivec2 viewportSize() const;
	GLFWwindow* getPtr();

private:
	static constexpr glm::ivec2 m_size{1900, 1000};
	static constexpr glm::ivec2 m_viewportPos{1200, 0};
	static constexpr glm::ivec2 m_viewportSize = m_size - m_viewportPos;

	GLFWwindow* m_windowPtr{};
	Scene* m_scene{};

	glm::vec2 m_lastCursorPos{};

	void updateViewport() const;
};
