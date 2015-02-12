/*
Skybox - Fragment Shader
*/
#version 400
in vec3 texCoord;

uniform samplerCube cubeMapTexture;

out vec4 fragment_color;

void main () {
	fragment_color = texture(cubeMapTexture, texCoord);
}