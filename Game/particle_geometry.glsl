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

// Uniform camera position
uniform vec3 cameraPosition;

// Output
out VertexData {
	vec2 tex_coords;
	float alpha;
} vertexOut;

void main() {
	//Up relative to camera extracted from view matrix
	vec4 cameraUp = vec4(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1], 0.0);

	//vector from camera to point, cameras position extracted from view matrix
	vec4 look = vec4(cameraPosition, 1.f) - vec4(gl_in[0].gl_Position.xyz, 1.0);

	//Particle right vector = camera up x look
	vec4 right = normalize(vec4(cross(cameraUp.xyz, look.xyz), 0.0));
	
	//Particle up vector = particle right x look
	vec4 up = normalize(vec4(cross(look.xyz, right.xyz), 0.0));
	
	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position - right + up);
	vertexOut.tex_coords = vec2(0.0, 0.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position - right - up );
	vertexOut.tex_coords = vec2(1.0,0.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + right + up );
	vertexOut.tex_coords = vec2(0.0, 1.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	gl_Position = projectionMatrix*viewMatrix*(gl_in[0].gl_Position + right - up );
	vertexOut.tex_coords = vec2(1.0, 1.0);
	vertexOut.alpha = vertexIn[0].alpha;
	EmitVertex();

	EndPrimitive();
}