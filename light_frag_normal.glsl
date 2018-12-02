#version 120

in vec2 UV;
in mat3 TBN;

uniform sampler2D  NormalTextureSampler;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fcolor;

void main()
{
	vec3 normal = texture2D(NormalTextureSampler, UV).rgb;
	normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
	
	vec3 n_TBN = TBN * normal;
	vec4 point_light_col = vec4(0.3,0.3,0.3, 1.0);
	float cosTheta = clamp( dot( normalize(n_TBN), normalize(vec3(1.0, 1.0, 1.0))), 0,1 );
	fcolor = point_light_col * cosTheta * 20;
	
}