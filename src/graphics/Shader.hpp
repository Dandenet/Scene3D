#pragma once

#include <string>
#include <vector>
#include <filesystem>


namespace graphics {

    class Shader
    {
    public:
        Shader();
        ~Shader();

        Shader(const Shader&) = delete;
        Shader(Shader&& other) noexcept;

        Shader& operator= (const Shader&) = delete;
        Shader& operator= (Shader&& other) noexcept;

        bool loadFromFile(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader) noexcept;

        bool bind();

    private:
        uint32_t m_shaderProgram;


        bool getFileContent(const std::filesystem::path& filename, std::vector<char>& buffer);
        bool compile(const char* vertexShaderSource, const char* fragmentShaderSource);
    };

}
