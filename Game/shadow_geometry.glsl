#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

// Uniform matrices
uniform mat4 lightModelMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
	// Calculate normal.
	vec3 n = cross(gl_in[1].gl_Position.xyz-gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz-gl_in[0].gl_Position.xyz);
	vec3 normal = normalMatrix * n;
	
	// Only render triangle if it's facing away from the light.
	float d = dot(normal, -vec3(lightViewMatrix * lightModelMatrix * gl_in[0].gl_Position));
	if (d < 0.0) {
		for(int i = 0; i < gl_in.length(); i++) {
			// Copy attributes
			gl_Position = lightProjectionMatrix * lightViewMatrix * lightModelMatrix * gl_in[i].gl_Position;
			// done with the vertex
			EmitVertex();
		}
		EndPrimitive();
	}
}