/*
Geometry pass fragment shader (first pass)
*/
#version 400
in VertexData {
	vec3 position;
	vec3 normal;
	vec2 tex_coords;
} vertexIn;

uniform sampler2D tDiffuse;

layout(location = 0) out vec3 positionOut;
layout(location = 1) out vec3 diffuseOut;
layout(location = 2) out vec3 normalsOut;

void main() {
	diffuseOut = texture(tDiffuse, vertexIn.tex_coords).rgb;
	positionOut = vertexIn.position;
	normalsOut = vertexIn.normal;
}
