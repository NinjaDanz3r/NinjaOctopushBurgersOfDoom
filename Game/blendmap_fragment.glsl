/*
Phong Lighting - Fragment Shader
Uses blend map (4 channels, rgba) for diffuse texture and does not have a specular highlight.
*/
#version 400
in VertexData {
	vec3 normal;
	vec3 tangent;
	vec2 tex_coords;
} vertexIn;

uniform sampler2D blendMapTexture;
uniform sampler2D redTexture;
uniform sampler2D greenTexture;
uniform sampler2D blueTexture;
uniform sampler2D alphaTexture;
uniform vec2 textureRepeat;

layout(location = 0) out vec3 diffuseOut;
layout(location = 1) out vec3 normalsOut;
layout(location = 2) out vec3 specularOut;

void main () {
	vec4 blendMap = texture(blendMapTexture, vertexIn.tex_coords);
	float sum = 1.0 / (blendMap.r + blendMap.g + blendMap.b + blendMap.a);
	diffuseOut = (blendMap.r * sum * texture(redTexture, vertexIn.tex_coords * textureRepeat) +
				  blendMap.g * sum * texture(greenTexture, vertexIn.tex_coords * textureRepeat) +
				  blendMap.b * sum * texture(blueTexture, vertexIn.tex_coords * textureRepeat) +
				  blendMap.a * sum * texture(alphaTexture, vertexIn.tex_coords * textureRepeat)).rgb;

	normalsOut = vertexIn.normal;
	specularOut = vec3(0.0, 0.0, 0.0);
}