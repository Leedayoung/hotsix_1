#version 120


in vec4 eye;
in vec3 cam_out;
in vec3 point1_light;
in vec3 point2_light;
in vec2 UV;
in vec3 T;
in vec3 B;
in vec3 N;

uniform sampler2D  NormalTextureSampler;
uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shiness;
uniform vec3 l_dir;

out vec4 fcolor;

void main()
{
	mat3 TBN = mat3(T, B, N);
	vec3 normal_out = texture2D(NormalTextureSampler, UV).rgb;
	normal_out = normalize(normal_out * 2.0 - 1.0);  // this normal is in tangent space
	normal_out = TBN * normal_out;
	float shine_point = 50000;
   
    vec4 spec = vec4(0.0);

    vec3 n = normalize(normal_out);
    vec3 e = normalize(vec3(eye));
    vec3 l_fixed = normalize(l_dir);
	vec3 l_point1 = normalize(point1_light);
	vec3 l_point2 = normalize(point2_light);
    float intensity1 = max(dot(n,l_fixed), 0.0);
	float intensity2 = max(dot(n,l_point1), 0.0);
	float intensity3 = max(dot(n,l_point2), 0.0);

    if (intensity1 > 0.0) {
        vec3 h = normalize(l_fixed + e);  
		float intSpec = max(dot(h,n), 0.0);
        spec += specular * pow(intSpec, shiness);
    }
	if (intensity2 > 0.0) {
        vec3 h = normalize(l_point1 + e);  
		float intSpec = max(dot(h,n), 0.0);
        spec += specular * pow(intSpec, shine_point);
    }
	if (intensity3 > 0.0) {
        vec3 h = normalize(l_point2 + e);  
		float intSpec = max(dot(h,n), 0.0);
        spec += specular * pow(intSpec, shine_point);
    }
	float intensity = (intensity1+intensity2+intensity3);
    fcolor = max(intensity * diffuse + spec, ambient);
	
}