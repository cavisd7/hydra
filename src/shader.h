#pragma once

#include <string>

enum ShaderType { VERTEX = 1, FRAGMENT };

class Shader 
{
private:
	std::string m_FilePath;
	unsigned int m_RendererId;
public:
	Shader(const std::string& filepath);
	~Shader();

	unsigned int GetRendererId() { return m_RendererId; };

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	unsigned int MakeShader(const std::string& path);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	int GetUniformLocation(const std::string& name);
};
