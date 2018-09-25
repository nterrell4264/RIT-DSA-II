/*
This is the vertex shader
*/

//specifies the version of the shader (and what features are enabled)
#version 400 core

// vertex attribute for position (loc = 0)
in vec3 position;

//entry point for the vertex shader
void main(void)
{
	gl_Position = vec4(position, 1.0);
}