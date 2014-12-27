/*
Clone incoming triangles 0.5 units along the normal vector (world space) and prepare values for Phong fragment shader.
*/
#version 400

// Input
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in VertexData {
	vec2 tex_coords;
} vertexIn[3];

// Uniform matrices.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;

// Output
out VertexData {
    vec3 position;
	vec3 normal;
	vec2 tex_coords;
} vertexOut;

void main() {
	// Calculate normal.
	vec3 n = cross(gl_in[1].gl_Position.xyz-gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz-gl_in[0].gl_Position.xyz);
	vec3 normal = normalize(normalMatrix * n);
	
	// Regular triangle.
	for(int i = 0; i < gl_in.length(); i++) {
		// Copy attributes
		vertexOut.position = vec3(viewMatrix * modelMatrix * gl_in[i].gl_Position);
		vertexOut.normal = normal;
		vertexOut.tex_coords = vertexIn[i].tex_coords;
		gl_Position = projectionMatrix * vec4(vertexOut.position, 1.0);
		
		// done with the vertex
		EmitVertex();
	}
	EndPrimitive();
}