/*
Phong Lighting - Fragment Shader
Normal map and specular map.
*/
#version 400
in VertexData {
	vec3 position;
	vec3 normal;
	vec2 tex_coords;
} vertexIn;

uniform sampler2D baseImage;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;

layout(location = 0) out vec3 positionOut;
layout(location = 1) out vec3 diffuseOut;
layout(location = 2) out vec3 normalsOut;
layout(location = 3) out vec3 specularOut;

void main () {
	diffuseOut = texture(baseImage, vertexIn.tex_coords).rgb;
	positionOut = vertexIn.position;
	normalsOut = vertexIn.normal;
	specularOut = texture(specularMap, vertexIn.tex_coords).rgb;
}