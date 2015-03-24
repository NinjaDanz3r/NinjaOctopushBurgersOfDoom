/*
Cull backfaces of incoming triangles and prepare values for Phong fragment shader.
*/
#version 400

// Input
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in VertexData {
	vec3 normal;
	vec3 tangent;
	vec2 tex_coords;
} vertexIn[3];

// Uniform matrices.
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;

// Output
out VertexData {
	vec3 normal;
	vec3 tangent;
	vec2 tex_coords;
} vertexOut;

void main() {
	// Calculate normal.
	vec3 n = cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz);
	vec3 normal = normalMatrix * n;
	
	// Only display triangle if it's facing the viewer.
	float d = dot(normal, -vec3(modelViewMatrix * gl_in[0].gl_Position));
	if (d > 0.0) {
		for(int i = 0; i < gl_in.length(); i++) {
			// Copy attributes
			vertexOut.normal =  normalize(normalMatrix * vertexIn[i].normal);
			vertexOut.tangent = normalize(normalMatrix * vertexIn[i].tangent);
			vertexOut.tex_coords = vertexIn[i].tex_coords;
			gl_Position = projectionMatrix * (modelViewMatrix * gl_in[i].gl_Position);
		
			// Done with the vertex
			EmitVertex();
		}
		EndPrimitive();
	}
}