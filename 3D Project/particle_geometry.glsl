/*
Particle geometry shader - Creates rectangles from points and faces them towards player
*/
#version 400

// Input
layout(points) in;
layout(triangle_strip, max_vertices=3) out;

// Uniform matrices.
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Output
out VertexData {
    vec3 position;
	vec2 texture;
} vertexOut;

void main() {
	vertexOut.position = projectionMatrix*viewMatrix*(gl_in.gl_position + vec3(-1,1,0));
	texture = vec2(0,0);
	emit_vertex();
	vertexOut.position = projectionMatrix*viewMatrix*(gl_in.gl_position + vec3(-1,-1,0));
	texture = vec2(1,0);
	emit_vertex();
	vertexOut.position = projectionMatrix*viewMatrix*(gl_in.gl_position + vec3(1,1,0));
	texture = vec2(0,1);
	emit_vertex();
	vertexOut.position = projectionMatrix*viewMatrix*(gl_in.gl_position + vec3(1,-1,0));
	texture = vec2(1,1);
	emit_vertex();
	EndPrimitive();
}