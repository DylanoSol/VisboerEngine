#pragma once

#include <string>

class ShaderContainer
{
public: 
	ShaderContainer(const char* vertexPath, const char* fragmentPath); 

	void UseShader(); 

	unsigned int GetShaderID(); 

	//Utility uniform functions
	void SetBool(const std::string& name, bool value) const; 
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	
	
private: 
	unsigned int m_shaderID; 
};

