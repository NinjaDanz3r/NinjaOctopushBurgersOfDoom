#version 400
in VertexData {
	vec2 tex_coords;
} vertexIn;

uniform sampler2D baseImage;

out vec4 fragment_color;
void main () {
	fragment_color = texture(baseImage, vertexIn.tex_coords);
}