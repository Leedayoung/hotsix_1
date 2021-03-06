#version 120

in vec3 vNormal;
in vec4 vPosition;
in vec2 _uv;
in vec3 tangent;
in vec3 bitangent;

uniform mat4 ctm;
uniform mat4 normal_model;
uniform mat4 view_model;
uniform vec4 cam;
uniform vec3 player;
uniform int dir;
uniform int flat;


out mat3 TBN;
out vec2 UV;
out vec3 eye;
out vec3 cam_out;
out vec3 point1_light;
out vec3 point2_light;
out float dist1;
out float dist2;

void main()
{
	gl_Position = ctm * vPosition;
	
	float w = 1.5;
    float h = 1.2;
    float al = 1.2;
	UV = _uv;
	vec3 T = (vec4(normalize(tangent),1)).xyz;
    vec3 N = (vec4(normalize(vNormal),1)).xyz;
    vec3 B = (vec4(normalize(bitangent),1)).xyz;
	TBN = mat3(T, B, N);

	eye = TBN*vec3(cam - (view_model * vPosition));
	cam_out = vec3(cam);
	vec3 light1_dir;
	vec3 light2_dir;
	 if(dir == 0){
    light1_dir = TBN * (player + vec3(w,h,al));
	light2_dir = TBN * (player + vec3(-w,h,al));
	}
   else if(dir == 1){
    light1_dir = TBN * (player + vec3(h,w,al));
	light2_dir = TBN * (player + vec3(h,-w,al));
   }
   else if(dir == 2){ 
    light1_dir = TBN * (player + vec3(w,-h,al));
	light2_dir = TBN * (player + vec3(-w,-h,al));
   }
   else if(dir == 3){  
    light1_dir = TBN * (player + vec3(-h,-w,al));
	light2_dir = TBN * (player + vec3(-h, w,al));
   }


	point1_light = TBN * (light1_dir - vec3(view_model * vPosition));
	point2_light = TBN * (light2_dir - vec3(view_model * vPosition));

	vec4 world_pos = view_model * vPosition;
   float diff_x1 = world_pos.x - light1_dir.x;
   float diff_y1 = world_pos.y - light1_dir.y;
   float diff_z1 = world_pos.z - light1_dir.z;
   dist1 = sqrt(diff_x1*diff_x1 + diff_y1*diff_y1 + diff_z1 * diff_z1);
   float diff_x2 = world_pos.x - light2_dir.x;
   float diff_y2 = world_pos.y - light2_dir.y;
   float diff_z2 = world_pos.z - light2_dir.z;
   dist2 = sqrt(diff_x2*diff_x2 + diff_y2*diff_y2 + diff_z2 * diff_z2);
   dist1+=1;
   dist2+=1;

}