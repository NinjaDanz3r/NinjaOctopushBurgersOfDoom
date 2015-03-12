/*
Shadow mapping fragment shader
*/
#version 400

in vec3 texCoord;

out float fragment_color;

void main(){
	float depth = texture(tShadowMap, texCoord);
	depth = 1.0 - (1.0 - depth) * 25.0;
	fragment_color = vec4(depth);
}
