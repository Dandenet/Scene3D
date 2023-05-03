#include <GL/glew.h>
#include <memory>

#include "Mesh.hpp"

namespace graphics
{
    Mesh::Mesh() : 
        m_vbo(0), m_vao(0), m_size(0)
    {
    }

    Mesh::~Mesh()
    {
        if (m_vbo)
        {
            glDeleteBuffers(1, &m_vbo);
        }

        if (m_vao)
        {
            glDeleteVertexArrays(1, &m_vao);
        }

    }

    Mesh::Mesh(Mesh&& other) noexcept :
        m_vbo(std::move(other.m_vbo)),
        m_vao(std::move(other.m_vao)),
        m_size(std::move(other.m_size))
    {
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept
    {
        if (m_vbo)
        {
            glDeleteBuffers(1, &m_vbo);
        }

        if (m_vao)
        {
            glDeleteVertexArrays(1, &m_vao);
        }

        m_vbo = std::move(other.m_vbo);
        m_vao = std::move(other.m_vao);
        m_size = std::move(other.m_size);

        return *this;
    }

    bool Mesh::create(size_t vertexCount)
    {
        m_size = vertexCount;

        if (!m_vbo)
        {
            glGenBuffers(1, &m_vbo);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_size, nullptr, GL_STREAM_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return true;
    }

    bool Mesh::update(const Vertex* vertices)
    {
        if (!m_vbo)
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
        glBindVertexArray(0);

        return true;
    }

    void Mesh::draw(uint32_t primitive)
    {
        glBindVertexArray(m_vao);
        glDrawArrays(primitive, 0, m_size);
        glBindVertexArray(0);
    }

}