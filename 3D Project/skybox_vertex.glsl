/*
Skybox - Vertex Shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 texCoord;

void main () {
	vec4 VP_position = projectionMatrix * viewMatrix * vec4(vertex_position, 1.0);
	gl_Position = VP_position.xyww;
	texCoord = vertex_position;
}