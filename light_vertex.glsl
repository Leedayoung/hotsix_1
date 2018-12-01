#version 120

in vec4 vPosition;
in vec3 vNormal;

uniform mat4 ctm;
uniform mat4 view_model;
uniform mat3 normal_mtx;

out vec4 eye;
out vec3 normal_out;

void main()
{
   normal_out = normalize(normal_mtx * vNormal);
   eye = -(view_model * vPosition);
   gl_Position = ctm * vPosition;
}