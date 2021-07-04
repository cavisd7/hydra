#include "shader.h"

#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static std::string ReadFileAsString(const std::string& path, ShaderType type) 
{
	std::string ext = type == 1 ? ".vert" : ".frag";
	std::string result;

	std::cout << "Looking for file: " << path + ext << std::endl;

	std::ifstream file(path + ext, std::ios::in | std::ios::binary);
	if (file) {
		file.seekg(0, std::ios::end);
		result.resize((size_t)file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&result[0], result.size());
		file.close();
	} else {
		std::cout << "[ERROR] Could not open file!" << std::endl;
	};

	return result;
};

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererId(0) 
{
	m_RendererId = MakeShader(filepath);
};

Shader::~Shader() 
{
	glDeleteProgram(m_RendererId);
};

void Shader::Bind() const 
{
	glUseProgram(m_RendererId);
};

void Shader::Unbind() const 
{
	glUseProgram(0);
};

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
};

unsigned int Shader::MakeShader(const std::string& path) 
{
	std::string vertexSource = ReadFileAsString(path, VERTEX);
	std::string fragmentSource = ReadFileAsString(path, FRAGMENT);

	unsigned int program = glCreateProgram();

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
	glAttachShader(program, vertexShader);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
};

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
{
    unsigned int id = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);
    
    int isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) 
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "[ERROR] Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);

		return 0;
    };

    return id;
};

int Shader::GetUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1) 
	{
		std::cout << "[WARNING] Uniform: " << name << "Does not exist!" << std::endl;
	};

	return location;
};
