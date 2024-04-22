#include "ShaderContainer.h"

#include <glad/glad.h> 

#include <fstream>
#include <sstream>
#include <iostream>

ShaderContainer::ShaderContainer(const char* vertexPath, const char* fragmentPath)
{

}

void ShaderContainer::UseShader()
{
	glUseProgram(m_ShaderID); 
}

unsigned int ShaderContainer::GetShaderID()
{
	return m_ShaderID; 
}

void ShaderContainer::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (int)value);
}

void ShaderContainer::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void ShaderContainer::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}
