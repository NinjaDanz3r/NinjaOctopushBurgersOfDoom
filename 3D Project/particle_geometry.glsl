/*
Particle geometry shader - Creates rectangles from points and faces them towards player
*/
#version 400

// Input
layout(points) in;
layout(triangle_list, max_vertices=3) out;

// Uniform matrices.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;

// Output
out VertexData {
    vec3 position;
} vertexOut;

void main() {
	
}