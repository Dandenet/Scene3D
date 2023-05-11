#include <GL/glew.h>
#include <memory>

#include "Texture.hpp"

namespace graphics
{
    Texture::Texture() : 
        m_texture{}, m_width{}, m_height{}, m_hasAlpha{}
    {
    }

    Texture::~Texture()
    {
        if (m_texture)
        {
            glDeleteTextures(1, &m_texture);
        }
    }

    Texture::Texture(Texture&& other) noexcept :
        m_texture(std::move(other.m_texture)),
        m_width (std::move(other.m_width)), 
        m_height(std::move(other.m_height)),
        m_hasAlpha(std::move(other.m_hasAlpha))
    {
        other.m_texture = 0;
        other.m_width = 0;
        other.m_height = 0;
        other.m_hasAlpha = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if (this == &other)
            return *this;

        if (m_texture)
        {
            glDeleteTextures(1, &m_texture);
        }

        m_texture = std::move(other.m_texture);
        m_width = std::move(other.m_width);
        m_height = std::move(other.m_height);
        m_hasAlpha = std::move(other.m_hasAlpha);

        other.m_texture = 0;
        other.m_width = 0;
        other.m_height = 0;
        other.m_hasAlpha = 0;

        return *this;
    }

    bool Texture::create(uint32_t width, uint32_t height, bool hasAlpha)
    {
        m_width = width;
        m_height = height;
        m_hasAlpha = hasAlpha;

        if (!m_texture)
        {
            glGenTextures(1, &m_texture);
        }

        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLint format = m_hasAlpha ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 
                                    0, format, GL_UNSIGNED_BYTE, nullptr);


        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    }

    bool Texture::update(const uint8_t* buffer)
    {
        if (!m_texture)
        {
            return false;
        }

        glBindTexture(GL_TEXTURE_2D, m_texture);

        GLenum format = m_hasAlpha ? GL_RGBA : GL_RGB;
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 
                        m_width, m_height, format, GL_UNSIGNED_BYTE, buffer);
        

        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    void Texture::bind()
    {
        if (m_texture)
        {
            glBindTexture(GL_TEXTURE_2D, m_texture);
        }
    }

}