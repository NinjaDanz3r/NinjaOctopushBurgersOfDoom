/*
Shadow mapping fragment shader
*/
#version 400

in vec2 texCoord;

uniform sampler2D tShadowMap;

out vec4 fragment_color;

void main(){
	float depth = texture(tShadowMap, texCoord).x;
	depth = 1.0 - (1.0 - depth) * 25.0;
	fragment_color = vec4(depth);
}
