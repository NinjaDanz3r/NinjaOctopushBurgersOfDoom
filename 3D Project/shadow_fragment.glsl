/*
Shadow mapping fragment shader
*/
#version 400

in vec3 modelPos;

uniform vec4 lightPosition;

out float fragment_color;

void main(){
	vec3 lightVertex = modelPos - lightPosition;
	float distance = lenght(lightVertex);
	fragment_color = distance;
}
