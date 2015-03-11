/*
Phong Lighting - Fragment Shader
Uses blend map (4 channels, rgba) for diffuse texture and does not have a specular highlight.
*/
#version 400
in VertexData {
	vec3 position;
	vec3 normal;
	vec2 tex_coords;
} vertexIn;

uniform sampler2D blendMap;
uniform sampler2D redTexture;
uniform sampler2D greenTexture;
uniform sampler2D blueTexture;
uniform sampler2D alphaTexture;
uniform vec2 textureRepeat;

uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;

out vec4 fragment_color;

// Ambient, diffuse and specular lighting.
vec3 ads() {
	vec3 n = normalize(vertexIn.normal);
	vec3 s = normalize(vec3(lightPosition) - vertexIn.position);
	vec3 v = normalize(vec3(-vertexIn.position));
	vec3 r = reflect(-s, n);
	vec3 diffuseLight = diffuseKoefficient * max(dot(s, n), 0.0);
	vec3 Ka = vec3(0.2, 0.2, 0.2);
	return lightIntensity * (Ka + diffuseLight);
}

void main () {
	vec4 blendMap = texture(blendMap, vertexIn.tex_coords);
	float sum = blendMap.r + blendMap.g + blendMap.b + blendMap.a;
	vec4 diffuse = blendMap.r / sum * texture(redTexture, vertexIn.tex_coords * textureRepeat) +
				   blendMap.g / sum * texture(greenTexture, vertexIn.tex_coords * textureRepeat) +
				   blendMap.b / sum * texture(blueTexture, vertexIn.tex_coords * textureRepeat) +
				   blendMap.a / sum * texture(alphaTexture, vertexIn.tex_coords * textureRepeat);

	fragment_color = diffuse * vec4(ads(), 1.0);
}