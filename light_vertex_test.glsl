#version 120

in vec3 vNormal;
in vec3 vNormal_flat;
in vec4 vPosition;

uniform int flat;
uniform mat4 ctm;
uniform mat4 view_model;

out vec3 normal_out;

void main()
{
	vec4 u_vNormal;
	if(flat == 0){
		u_vNormal = vec4(vNormal_flat,1);
	}else{
		u_vNormal = vec4(vNormal,1);
	}
	u_vNormal = view_model * u_vNormal;
	normal_out = normalize(u_vNormal.xyz);
	gl_Position = ctm * vPosition;
}