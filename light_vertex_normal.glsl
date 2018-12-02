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


out mat3 TBN;
out vec2 UV;
out vec3 eye;
out vec3 normal_out;
out vec3 cam_out;
out vec3 point1_light;
out vec3 point2_light;

void main()
{
	gl_Position = ctm * vPosition;
	
	float w = 1.0;
    float h = 1.2;
    float al = 1.0;
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
}