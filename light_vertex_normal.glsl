#version 120

in vec3 vNormal;
in vec4 vPosition;
in vec2 _uv;
in vec3 tangent;
in vec3 bitangent;

uniform mat4 ctm;
uniform mat4 normal_model;
uniform mat4 view_model;
uniform vec4 cam;
uniform vec3 player;


out vec3 T;
out vec3 N;
out vec3 B;

out vec2 UV;
out vec4 eye;
out vec3 normal_out;
out vec3 cam_out;
out vec3 point1_light;
out vec3 point2_light;

void main()
{
	gl_Position = ctm * vPosition;
	T = (normal_model * vec4(normalize(tangent),1)).xyz;
    N = (normal_model * vec4(normalize(vNormal),1)).xyz;
    B = (normal_model * vec4(normalize(bitangent),1)).xyz;
	
	UV = _uv;

	eye = cam - (view_model * vPosition);
	cam_out = vec3(cam);
	vec3 light1_dir = player + vec3(1.0,1.0,1.0);
	vec3 light2_dir = player + vec3(-1.0,-1.0,1.0);
	point1_light = light1_dir - vec3(view_model * vPosition);
	point2_light = light2_dir - vec3(view_model * vPosition);
}