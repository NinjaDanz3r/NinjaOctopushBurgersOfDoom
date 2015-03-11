/*
Passthrough vertex shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in float vertex_alpha;

out VertexData {
	float alpha;
} vertexOut;

void main () {
	vertexOut.alpha = vertex_alpha;
	gl_Position = vec4(vertex_position, 1.0f);
}