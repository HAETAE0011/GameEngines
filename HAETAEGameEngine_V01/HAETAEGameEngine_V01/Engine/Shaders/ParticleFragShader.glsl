#version 450 core

in vec2 TexCoords;

out vec4 colour;

uniform vec3 ParticleColour;
uniform sampler2D inputTexture;

void main(){

	vec4 tmpColour =  vec4(ParticleColour, 1.0f) * texture(inputTexture, TexCoords);
	colour = tmpColour;
}