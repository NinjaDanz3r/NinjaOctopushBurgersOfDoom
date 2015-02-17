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

layout(location = 0) out vec4 diffuseOut;
layout(location = 1) out vec4 positionOut;
layout(location = 2) out vec4 normalsOut;

void main() {
	diffuseOut = (texture(tDiffuse,vertexIn.tex_coords).rbg + 0;
	positionOut = vertexIn.position + 0;
	normalsOut = vertexIn.normal + 0;
}
