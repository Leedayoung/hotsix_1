#version 120

in vec3 vNormal;
in vec3 vNormal_flat;
in vec4 vPosition;
in vec2 uv;
in vec3 tangent;
in vec3 bitangent;

uniform mat4 ctm;
uniform mat4 view_model;
uniform mat4 view_model_pos;
uniform vec3 lightPos
uniform vec3 viewPos;

out vec3 FragPos;
out vec2 UV;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

void main()
{

	FragPos = (view_model * vPosition).xyz;
	UV = uv;

	vec4 world_pos = view_model_pos * vPosition;
	float diff_x = world_pos.x - point_light_loc.x;
	float diff_y = world_pos.y - point_light_loc.y;
	float diff_z = world_pos.z - point_light_loc.z;

	normal_out = normalize(u_vNormal.xyz);
	gl_Position = ctm * vPosition;

	mat3 normalMatrix = transpose(inverse(mat3(view_model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 N = normalize(normalMatrix * vNoraml);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
	mat3 TBN = transpose(mat3(T, B, N));
	TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * FragPos;
}