#include "mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<glm::vec2>& vertices)
{
	createVBO(vertices);
	update(vertices);
	createVAO();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void Mesh::render() const
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, m_vertexCount);
	glBindVertexArray(0);
}

void Mesh::update(const std::vector<glm::vec2>& vertices)
{
	m_vertexCount = vertices.size();
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(glm::vec2)),
		vertices.data(), GL_DYNAMIC_DRAW);
}

void Mesh::createVBO(const std::vector<glm::vec2>& vertices)
{
	glGenBuffers(1, &m_VBO);
}

void Mesh::createVAO()
{
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
