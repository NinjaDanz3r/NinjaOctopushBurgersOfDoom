/*
Lighting pass vertex shader (second pass)
*/
#version 400

layout(location = 0) in vec2 vertex_position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
	gl_Position = vec4(vertex_position, 0.0, 1.0);
}