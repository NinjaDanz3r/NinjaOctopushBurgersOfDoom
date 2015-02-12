/*
Phong Lighting - Fragment Shader
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
	//fixa vec4.w (alpha)
	diffuseOut = texture(tDiffuse,vertexIn.tex_coords).rbg;
	positionOut = position;
	normalsOut = normals;
}