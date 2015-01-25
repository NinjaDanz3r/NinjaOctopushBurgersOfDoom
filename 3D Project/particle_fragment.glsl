#version 400
in VertexData {
	vec3 position;
	vec2 texture;
} vertexIn;

uniform sampler2D baseImage;

out vec4 fragment_color;
void main () {
	fragment_color = texture(baseImage, vertexIn.tex_coords);
}