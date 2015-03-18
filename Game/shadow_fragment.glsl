/*
Shadow mapping fragment shader
*/
#version 400

//layout(location = 0) out float fragment_depth;
layout(location = 0) out vec4 fragment_color;

void main(){
	fragment_color = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 1.0);
}
