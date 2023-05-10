#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>

#include <glm/glm.hpp>



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

        bool setUniform(const std::string& uniform, const glm::mat4& mat);

    private:
        uint32_t m_shaderProgram;
        std::unordered_map<std::string, int> m_uniformTable;


        bool getFileContent(const std::filesystem::path& filename, std::vector<char>& buffer);
        bool compile(const char* vertexShaderSource, const char* fragmentShaderSource);
        int getUniformLocation(const std::string& uniform);
    };

}
