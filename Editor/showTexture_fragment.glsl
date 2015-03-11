/*
Show texture fragment shader
*/
#version 400

uniform sampler2D baseImage;
uniform vec2 screenSize;

out vec4 fragment_color;

// Calculate texcoord
vec2 calculateTexCoord() {
	return gl_FragCoord.xy / screenSize;
}

void main() {
	vec2 texCoord = calculateTexCoord();
	fragment_color = vec4(texture(baseImage, texCoord).rgb, 1.0);
}
