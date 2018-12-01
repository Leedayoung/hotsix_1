#version 120

in vec4 eye;
in vec3 normal_out;

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shiness;
uniform vec3 l_dir;

out vec4 fcolor;

void main()
{
   vec4 spec = vec4(0.0);

    vec3 n = normalize(normal_out);
    vec3 e = normalize(vec3(eye));
 
    float intensity = max(dot(n,l_dir), 0.0);

    if (intensity > 0.0) {
        vec3 h = normalize(l_dir + e);  
		float intSpec = max(dot(h,n), 0.0);
        spec = specular * pow(intSpec, shiness);
    }
    fcolor = max(intensity *  diffuse + spec, ambient);
}