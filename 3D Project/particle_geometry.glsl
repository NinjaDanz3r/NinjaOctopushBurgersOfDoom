/*
Particle geometry shader - Creates rectangles from points and faces them towards player
*/
#version 400

// Input
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

// Uniform matrices.
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Output
out VertexData {
	vec2 tex_coord;
} vertexOut;

void main() {
	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + vec4(-1.0, 1.0, 0.0, 0.0) );
	vertexOut.tex_coord = vec2(0.0, 0.0);
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + vec4(-1.0, -1.0, 0.0, 0.0) );
	vertexOut.tex_coord = vec2(1.0,0.0);
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + vec4(1.0 ,1.0, 0.0, 0.0) );
	vertexOut.tex_coord = vec2(0.0, 1.0);
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + vec4(1.0, -1.0, 0.0, 0.0) );
	vertexOut.tex_coord = vec2(1.0, 1.0);
	EmitVertex();

	EndPrimitive();
}