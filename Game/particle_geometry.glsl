/*
Particle geometry shader - Creates rectangles from points and faces them towards player
*/
#version 400

// Input
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in VertexData {
	float alpha;
} vertexIn[1];

// Uniform matrices.
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Output
out VertexData {
	vec2 tex_coords;
	float alpha;
} vertexOut;

void main() {
	vec4 cameraRight = vec4(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0], 0.0);		//Right, relative to camera
	vec4 cameraUp = vec4(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1], 0.0);		//Up, relative to camera

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position - cameraRight + cameraUp);
	vertexOut.tex_coords = vec2(0.0, 0.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position - cameraRight - cameraUp );
	vertexOut.tex_coords = vec2(1.0,0.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + cameraRight + cameraUp );
	vertexOut.tex_coords = vec2(0.0, 1.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + cameraRight - cameraUp );
	vertexOut.tex_coords = vec2(1.0, 1.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	EndPrimitive();
}