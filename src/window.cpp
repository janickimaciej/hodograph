#include "window.hpp"

#include <string>

Window::Window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	static const std::string windowTitle = "hodograph";
	m_windowPtr = glfwCreateWindow(m_size.x, m_size.y, windowTitle.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_windowPtr, this);
	glfwMakeContextCurrent(m_windowPtr);
	glfwSwapInterval(1);

	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	glViewport(m_viewportPos.x, m_viewportPos.y, m_viewportSize.x, m_viewportSize.y);
}

Window::~Window()
{
	glfwTerminate();
}

glm::ivec2 Window::viewportSize() const
{
	return m_viewportSize;
}

void Window::setWindowData(Scene& scene, GUI& gui)
{
	m_scene = &scene;
	m_gui = &gui;
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_windowPtr);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_windowPtr);
}

void Window::pollEvents() const
{
	glfwPollEvents();
}

GLFWwindow* Window::getPtr()
{
	return m_windowPtr;
}
