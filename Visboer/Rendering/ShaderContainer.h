#pragma once

#include <string>
#include <glm/glm.hpp>

class ShaderContainer
{
public: 
	ShaderContainer(const char* vertexPath, const char* fragmentPath); 

	void UseShader(); 
	void RecompileShader(); 

	unsigned int GetShaderID(); 

	//Utility uniform functions
	void SetBool(const std::string& name, bool value) const; 
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	void SetMat4(const std::string& name, const glm::mat4& mat); 
	
	
private: 
	void CompileShader(); 
	void DeleteShader(); 

	const char* m_vertexPath; 
	const char* m_fragmentPath; 

	unsigned int m_shaderID; 
};

