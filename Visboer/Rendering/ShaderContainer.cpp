#include "ShaderContainer.h"

#include <glad/glad.h> 

#include <fstream>
#include <sstream>
#include <iostream>

ShaderContainer::ShaderContainer(const char* vertexPath, const char* fragmentPath)
{
	m_vertexPath = vertexPath; 
	m_fragmentPath = fragmentPath; 

	CompileShader(); 
}

void ShaderContainer::UseShader()
{
	glUseProgram(m_shaderID); 
}

unsigned int ShaderContainer::GetShaderID()
{
	return m_shaderID; 
}

void ShaderContainer::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), (int)value);
}

void ShaderContainer::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void ShaderContainer::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void ShaderContainer::CompileShader()
{
	//Get the source code from the desired file paths. 
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	//Add exception throwing
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	//Ensure that you are able to catch errors while running this code. 
	try
	{
		//Open files so they can be read
		vertexShaderFile.open(m_vertexPath);
		fragmentShaderFile.open(m_fragmentPath);

		//Read buffers into streams
		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		//Close files 
		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		printf("Could not read shader \n");
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	//Compile shaders

	unsigned int vertex;
	unsigned int fragment;

	//Error logging requirements
	int success;
	char infoLog[512];

	//Vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);

	//Print compile errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Vertex shader compilation failed\n" << infoLog << std::endl;
	}

	//Fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);

	//Print compile errors
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Fragment shader compilation failed\n" << infoLog << std::endl;
	}

	//Create shader program
	m_shaderID = glCreateProgram();

	glAttachShader(m_shaderID, vertex);
	glAttachShader(m_shaderID, fragment);

	glLinkProgram(m_shaderID);

	//Print linking errors
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
		std::cout << "Shader linking failed\n" << infoLog << std::endl;
	}

	//Delete the shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
