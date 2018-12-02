#version 120

in vec3 vNormal;
in vec4 vPosition;

uniform mat4 ctm;
uniform mat4 view_model;
uniform mat3 normal_mtx;

out vec4 eye;
out vec3 normal_out;

void main()
{
   normal_out = normalize(vNormal);
   eye = -(view_model * vPosition);
   gl_Position = ctm * vPosition;
}