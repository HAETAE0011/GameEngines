#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform vec3 pos;

void main(){


	TexCoords = texCoords;
	//gl_Position = proj * model * view * vec4((position.x + pos.x), (position.y + pos.y), inversesqrt(0.1 * len), 1.0f);
	gl_Position = proj * model * view * vec4(pos.x + position.x, pos.y + position.y , pos.z, 1.0f);
}