#version 120
attribute vec3 vertexPosition_modelspace;

varying vec2 UV;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main()
{
	gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace, 1);
}