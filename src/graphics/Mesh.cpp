#include <GL/glew.h>
#include <memory>

#include "Mesh.hpp"

namespace graphics
{
    Mesh::Mesh() : 
        m_vbo(0), m_vao(0), m_ebo(0), 
        m_size(0), m_indicesCount(0)
    {
    }

    Mesh::~Mesh()
    {
        if (m_vbo)
        {
            glDeleteBuffers(1, &m_vbo);
        }

        if (m_vbo)
        {
            glDeleteBuffers(1, &m_ebo);
        }

        if (m_vao)
        {
            glDeleteVertexArrays(1, &m_vao);
        }

    }

    Mesh::Mesh(Mesh&& other) noexcept :
        m_vbo(std::move(other.m_vbo)),
        m_vao(std::move(other.m_vao)),
        m_ebo(std::move(other.m_ebo)),
        m_size(std::move(other.m_size)),
        m_indicesCount(std::move(other.m_indicesCount))
    {
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept
    {
        if (m_vbo)
        {
            glDeleteBuffers(1, &m_vbo);
        }

        if (m_ebo)
        {
            glDeleteBuffers(1, &m_ebo);
        }

        if (m_vao)
        {
            glDeleteVertexArrays(1, &m_vao);
        }

        m_vbo = std::move(other.m_vbo);
        m_vao = std::move(other.m_vao);
        m_ebo = std::move(other.m_ebo);
        m_size = std::move(other.m_size);
        m_indicesCount = std::move(other.m_indicesCount);

        return *this;
    }

    bool Mesh::create(size_t vertexCount, size_t indicesCount)
    {
        m_size = vertexCount;
        m_indicesCount = indicesCount;

        if (!m_vbo)
        {
            glGenBuffers(1, &m_vbo);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_size, nullptr, GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        if (!m_ebo)
        {
            glGenBuffers(1, &m_ebo);
        }



        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indicesCount, nullptr, GL_STREAM_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return true;
    }

    bool Mesh::update(const Vertex* vertices, const unsigned int* indices)
    {
        if (!m_vbo || !m_ebo)
        {
            return false;
        }
            

        if (!m_vao)
        {
            glGenVertexArrays(1, &m_vao);
        }

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_size, vertices);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, point));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * m_indicesCount, indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        return true;
    }

    void Mesh::draw(uint32_t primitive)
    {
        glBindVertexArray(m_vao);
        glDrawArrays(primitive, 0, m_size);
        glBindVertexArray(0);
    }

    void Mesh::drawElements(uint32_t primitive)
    {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glDrawElements(primitive, m_indicesCount, GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

}