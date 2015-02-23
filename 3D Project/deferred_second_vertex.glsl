/*
Lighting pass vertex shader (second pass)
*/
#version 400
const vec2 quadVertices[4] = { vec2(-0.5, -0.5), vec2(0.5, -0.5), vec2(-0.5, 0.5), vec2(0.5, 0.5) };
void main() {
    gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
}
/*
//Input
layout(location = 0) in vec3 position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	gl_Position = modelMatrix * projectionMatrix * viewMatrix * vec4(position, 1.0);
}*/