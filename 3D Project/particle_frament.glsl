#version 400
in VertexData {
	vec3 position;
} vertexIn;

uniform sampler2D baseImage;
uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;

out vec4 fragment_color;
void main () {
	fragment_color = texture(baseImage, vertexIn.tex_coords);
}