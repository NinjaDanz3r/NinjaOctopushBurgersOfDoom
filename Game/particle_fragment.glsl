#version 400
in VertexData {
	vec2 tex_coords;
	float alpha;
} vertexIn;

uniform sampler2D baseImage;

out vec4 fragment_color;
void main () {
	fragment_color = texture(baseImage, vertexIn.tex_coords);
	fragment_color.a *= vertexIn.alpha;
}