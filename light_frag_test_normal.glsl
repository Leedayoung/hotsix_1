#version 120

in vec3 FragPos;
in vec2 UV;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform sampler2D  NormalTextureSampler;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fcolor;

void main()
{
	vec3 normal = texture(NormalTextureSampler, UV).rgb;
	normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
	 vec3 color = vec3(1.0, 1.0, 0.0);
	 vec3 ambient = 0.1 * color;
	vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
	vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	vec3 specular = vec3(0.2) * spec;
    fcolor = vec4(ambient + specular, 1.0);
}