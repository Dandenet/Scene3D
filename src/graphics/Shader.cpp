#include <GL/glew.h>
#include <iostream>
#include <fstream>

#include "Shader.hpp"

namespace graphics {

	Shader::Shader() : 
		m_shaderProgram(0)
	{
	}

	Shader::~Shader()
	{
		if (m_shaderProgram)
		{
			glDeleteProgram(m_shaderProgram);
		}
	}

	Shader::Shader(Shader&& other) noexcept : 
		m_shaderProgram(std::move(other.m_shaderProgram))
	{

	}

	Shader& Shader::operator=(Shader&& other) noexcept
	{
		if (m_shaderProgram)
		{
			glDeleteProgram(m_shaderProgram);
		}

		m_shaderProgram = std::move(other.m_shaderProgram);
		
		return *this;
	}

	bool Shader::loadFromFile(const std::filesystem::path& vertexShaderFile, const std::filesystem::path& fragmentShaderFile) noexcept
	{
		std::vector<char> vertexShaderSource;
		if (!getFileContent(vertexShaderFile, vertexShaderSource)) 
		{
			std::cout << "failed to open vertex shader source file: " << vertexShaderFile << std::endl;
			return false;
		}

		std::vector<char> fragmentShaderSource;
		if (!getFileContent(fragmentShaderFile, fragmentShaderSource)) 
		{
			std::cout << "failed to open fragment shader source file: " << vertexShaderFile << std::endl;
			return false;
		}		

		return compile(vertexShaderSource.data(), fragmentShaderSource.data());
	}

	bool Shader::bind()
	{
		if (!m_shaderProgram)
			return false;

		glUseProgram(m_shaderProgram);

		return true;
	}

	bool Shader::getFileContent(const std::filesystem::path& filename, std::vector<char>& buffer)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			file.seekg(0, std::ios_base::end);
			std::ios::pos_type size = file.tellg();
			if (size > 0)
			{
				file.seekg(0, std::ios_base::beg);
				buffer.resize(size);
				file.read(buffer.data(), size);
				buffer.push_back('\0');
			}

			file.close();
			return true;
		}

		return false;
	}

	bool Shader::compile(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

	    GLint succes = false;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);

	    if(!succes) 
		{
		    int logsize;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logsize);

			std::vector<char> log(logsize);
			glGetShaderInfoLog(vertexShader, logsize, &logsize, log.data());
			std::cout << "Vertex shader error:" << std::endl << log.data() << std::endl;

			glDeleteShader(vertexShader);

			return false;
		}


		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			int logsize;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logsize);

			std::vector<char> log(logsize);
			glGetShaderInfoLog(fragmentShader, logsize, &logsize, log.data());
			std::cout << "Fragment shader error:" << std::endl << log.data() << std::endl;

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return false;
		}

		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);

		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			int logsize;
			glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &logsize);

			std::vector<char> log(logsize);
			glGetProgramInfoLog(m_shaderProgram, logsize, &logsize, log.data());
			std::cout << log.data() << std::endl;


			glDeleteProgram(m_shaderProgram);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return false;
		}

		glDetachShader(m_shaderProgram, vertexShader);
		glDetachShader(m_shaderProgram, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return true;
	}


} //namespace
