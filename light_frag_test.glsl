#version 120

in vec4 eye;
in vec3 normal_out;
in float dist;

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shiness;
uniform vec3 l_dir;
uniform vec4 LightColor;
out vec4 fcolor;


uniform vec3 point_light_dir;
uniform vec4 point_light_col;


void main()
{
   float cosTheta = clamp( dot( normalize(normal_out),normalize(l_dir)), 0,1 );
   float p_cosTheta = clamp( dot( normalize(normal_out),normalize(point_light_dir)), 0,1 );
   fcolor = LightColor * (cosTheta)+  point_light_col * (p_cosTheta /dist * 5);
}
