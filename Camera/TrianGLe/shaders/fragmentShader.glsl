/*
This is the fragment shader, and its main job is to determine the color for each pixel (fragment)
*/

//specifies the version of the shader (and what features are enabled)
#version 400 core

out vec4 color;

//entry point for the fragment shader
void main(void)
{
	color = vec4(.75, .75, 0, 1);
}