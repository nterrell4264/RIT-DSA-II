#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Shader
{
private:
	GLuint shaderLoc;
public:
	///<summary>Default constructor</summary>
	Shader();

	///<summary>Destructor</summary>
	~Shader();

	///<summary>Initializes a shader by loading in a .glsl file and compiling it</summary>
	///<param name='filePath'>A string specifying the path of the file</param>
	///<param name='shaderType'>GLenum representing the type</param>
	///<returns>Wether or note the compilation succeeds</returns>
	bool InitFromFile(std::string filePath, GLenum shaderType);

	///<summary>Initializes a shader by compiling a string</summary>
	///<param name='filePath'>A string that makes up the .glsl file</param>
	///<param name='shaderType'>GLenum representing the type</param>
	///<returns>Wether or note the compilation succeeds</returns>
	bool InitFromString(std::string shaderCode, GLenum shaderType);

	///<summary>The location of the shader</summary>
	GLuint GetShaderLoc() const { return shaderLoc; }
};