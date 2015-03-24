/*
Phong Lighting - Fragment Shader
Normal map and specular map.
*/
#version 400
in VertexData {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec2 tex_coords;
} vertexIn;

uniform sampler2D baseImage;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;

layout(location = 0) out vec3 diffuseOut;
layout(location = 1) out vec3 normalsOut;
layout(location = 2) out vec3 specularOut;

vec3 calculateNormal(vec3 normal, vec3 tangent, vec3 mapNormal) {
    vec3 n = normalize(normal);
    vec3 t = normalize(tangent);
    t = normalize(t - dot(t, n) * n);
    vec3 b = cross(t, n);
    vec3 mn = normalize(2.0 * mapNormal - vec3(1.0, 1.0, 1.0));
    mat3 TBN = mat3(t, b, n);
    return TBN * mn;
}

void main () {
	diffuseOut = texture(baseImage, vertexIn.tex_coords).rgb;
	normalsOut = calculateNormal(vertexIn.normal, vertexIn.tangent, texture(normalMap, vertexIn.tex_coords).rgb);
	specularOut = texture(specularMap, vertexIn.tex_coords).rgb;
}