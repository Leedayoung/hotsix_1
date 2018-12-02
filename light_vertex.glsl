#version 120

in vec3 vNormal;
in vec4 vPosition;

uniform mat4 ctm;
uniform mat4 view_model;
uniform mat3 normal_mtx;
uniform vec4 cam;
uniform vec3 player;
uniform int dir;

out vec4 eye;
out vec3 normal_out;
out vec3 cam_out;
out vec3 point1_light;
out vec3 point2_light;

void main()
{
   normal_out = normalize(normal_mtx*vNormal);
   eye = cam - (view_model * vPosition);
   gl_Position = ctm * vPosition;
   cam_out = vec3(cam);
   vec3 light1_dir;
   vec3 light2_dir;
   if(dir == 0){
    light1_dir = player + vec3(2.0,0.5,1.5);
	light2_dir = player + vec3(-2.0,0.5,1.5);
	}
   else if(dir == 1){
    light1_dir = player + vec3(0.5,2.0,1.5);
	light2_dir = player + vec3(0.5,-2.0,1.5);
   }
   else if(dir == 2){ 
    light1_dir = player + vec3(2.0,-0.5,1.5);
	light2_dir = player + vec3(-2.0,-0.5,1.5);
   }
   else if(dir == 3){  
    light1_dir = player + vec3(-0.5,-2.0,1.5);
	light2_dir = player + vec3(-0.5,2.0, 1.5);
   }
   point1_light = light1_dir - vec3(view_model * vPosition);
   point2_light = light2_dir - vec3(view_model * vPosition);
}