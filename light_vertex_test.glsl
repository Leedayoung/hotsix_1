#version 120

in vec3 vNormal;
in vec3 vNormal_flat;
in vec4 vPosition;

uniform int flat;
uniform mat4 ctm;
uniform mat4 view_model;
uniform mat4 view_model_pos;
uniform vec3 point_light_loc;

out float dist;
out vec3 normal_out;

void main()
{
	vec4 u_vNormal;
	if(flat == 0){
		u_vNormal = vec4(vNormal_flat,1);
		
	}else{
		u_vNormal = vec4(vNormal,1);
	}
	vec4 world_pos = view_model_pos * vPosition;
	float diff_x = world_pos.x - point_light_loc.x;
	float diff_y = world_pos.y - point_light_loc.y;
	float diff_z = world_pos.z - point_light_loc.z;
	dist = sqrt(diff_x*diff_x + diff_y*diff_y + diff_z * diff_z);
	u_vNormal = view_model * u_vNormal;
	normal_out = normalize(u_vNormal.xyz);
	gl_Position = ctm * vPosition;
}