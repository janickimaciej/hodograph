#pragma once

#include <cstddef>
#include <vector>

#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh(const std::vector<glm::vec2>& vertices);
	~Mesh();

	void render() const;
	void update(const std::vector<glm::vec2>& vertices);

private:
	std::size_t m_vertexCount{};
	unsigned int m_VBO{};
	unsigned int m_VAO{};

	void createVBO(const std::vector<glm::vec2>& vertices);
	void createVAO();
};
