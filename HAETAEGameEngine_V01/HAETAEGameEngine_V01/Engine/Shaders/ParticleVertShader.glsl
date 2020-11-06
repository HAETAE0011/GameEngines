#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform vec3 pos;

void main(){
	vec4 dist = view * model * vec4(position, 0.0f, 1.0f);
	float len = length(vec3(dist.x, dist.y, dist.z));

	TexCoords = texCoords;
	//gl_Position = proj * model * view * vec4(position, inversesqrt(0.1 * len), 1.0f);
	gl_Position = proj * model * view * vec4(position, inversesqrt(0.1 * len), 1.0f);
	//gl_Position = proj * model * view * vec4(position, inversesqrt(len), 1.0f);
}