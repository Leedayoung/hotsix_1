#version 120

in vec4 vPosition;
uniform mat4 ctm;
uniform vec4 color;
out vec4 vColor;
void main()
{
    gl_Position = ctm * vPosition;
	vColor = color;
	
}