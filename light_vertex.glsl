#version 120

in vec3 vNormal;
in vec4 vPosition;

uniform mat4 ctm;
uniform mat4 view_model;
uniform mat3 normal_mtx;
uniform vec4 cam;

out vec4 eye;
out vec3 normal_out;
out vec3 cam_out;

void main()
{

   normal_out = normalize(normal_mtx*vNormal);
   eye = cam - (view_model * vPosition);
   gl_Position = ctm * vPosition;
   cam_out = vec3(cam);
}