#version 120

in vec4 eye;
in vec3 normal_out;
in vec3 cam_out;
in vec3 point1_light;
in vec3 point2_light;

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shiness;
uniform vec3 l_dir;
uniform float light_power1;
uniform float light_power2;
uniform float light_power3;
out vec4 fcolor;

void main()
{
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
        spec += light_power1 * specular * pow(intSpec, shiness);
    }
	if (intensity2 > 0.0) {
        vec3 h = normalize(l_point1 + e);  
		float intSpec = max(dot(h,n), 0.0);
        spec += light_power2 * specular * pow(intSpec, shiness);
    }
	if (intensity3 > 0.0) {
        vec3 h = normalize(l_point2 + e);  
		float intSpec = max(dot(h,n), 0.0);
        spec += light_power3 *specular * pow(intSpec, shiness);
    }
	float intensity = (light_power1*intensity1+light_power2*intensity2+light_power3*intensity3);
    fcolor = max(intensity * diffuse + spec, ambient);
}