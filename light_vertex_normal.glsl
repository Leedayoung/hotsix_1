#version 120

in vec3 vNormal;
in vec4 vPosition;
in vec2 _uv;
in vec3 tangent;
in vec3 bitangent;

uniform mat4 ctm;
uniform mat4 view_model;
uniform mat4 view_model_pos;
uniform vec3 lightPos;
uniform vec3 viewPos;

out mat3 TBN;
out vec2 UV;

void main()
{
	gl_Position = ctm * vPosition;

	UV = _uv;
	vec3 T = (view_model * vec4(normalize(tangent),1)).xyz;
    vec3 N = (view_model * vec4(normalize(vNormal),1)).xyz;
    vec3 B = (view_model * vec4(normalize(bitangent),1)).xyz;
	TBN = transpose(mat3(T, B, N));
}