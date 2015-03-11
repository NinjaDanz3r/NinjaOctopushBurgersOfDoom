/*
Shadow mapping vertex shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 modelPos;

void main () {dsa
	vec4 pos4 = vec4(vertex_position, 1.0);
	gl_Position =  modelMatrix * viewMatrix * projectionMatrix * pos4;
	modelPos = (modelMatrix * pos4).xyz;
}