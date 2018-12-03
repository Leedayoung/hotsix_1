#version 120

in vec3 vNormal;
in vec4 vPosition;	
in vec3 vNormal_flat;

uniform mat4 ctm;
uniform mat4 view_model;
uniform mat3 normal_mtx;
uniform vec4 cam;
uniform vec3 player;
uniform int dir;
uniform int flat;

out vec4 eye;
out vec3 normal_out;
out vec3 cam_out;
out vec3 point1_light;
out vec3 point2_light;
out float dist1;
out float dist2;

void main()
{
   vec3 u_vNormal;
	if(flat == 0){
		u_vNormal = vNormal_flat;
		
	}
	else{
		u_vNormal = vNormal;
	}
   float w = 1.5;
   float h = 1.2;
   float al = 1.5;
   normal_out = normalize(normal_mtx*u_vNormal);
   eye = cam - (view_model * vPosition);
   gl_Position = ctm * vPosition;
   cam_out = vec3(cam);
   vec3 light1_dir;
   vec3 light2_dir;
   if(dir == 0){
    light1_dir = player + vec3(w,h,al);
	light2_dir = player + vec3(-w,h,al);
	}
   else if(dir == 1){
    light1_dir = player + vec3(h,w,al);
	light2_dir = player + vec3(h,-w,al);
   }
   else if(dir == 2){ 
    light1_dir = player + vec3(w,-h,al);
	light2_dir = player + vec3(-w,-h,al);
   }
   else if(dir == 3){  
    light1_dir = player + vec3(-h,-w,al);
	light2_dir = player + vec3(-h,w, al);
   }
   point1_light = light1_dir - vec3(view_model * vPosition);
   point2_light = light2_dir - vec3(view_model * vPosition);

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