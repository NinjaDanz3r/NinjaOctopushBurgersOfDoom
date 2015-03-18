/*
Shadow mapping fragment shader
*/
#version 400

//layout(location = 0) out float fragment_depth;
layout(location = 0) out vec4 fragment_color;

void main(){
	float fragment_depth = gl_FragCoord.z;
	fragment_color = vec4(fragment_depth, 1.0,0.0,1.0);
}
