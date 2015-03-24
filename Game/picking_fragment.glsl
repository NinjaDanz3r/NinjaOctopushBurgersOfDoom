/*
Phong Lighting - Fragment Shader
Normal map and specular map.
*/
#version 400
in VertexData {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec2 tex_coords;
} vertexIn;

uniform sampler2D baseImage;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;

uniform int isHit;
uniform int currentlyDrawingObject;
uniform int closestObjectHit;

out vec4 fragment_color;

// Ambient, diffuse and specular lighting.
vec3 ads() {
	vec3 n = normalize(vertexIn.normal);
	vec3 s = normalize(vec3(lightPosition) - vertexIn.position);
	vec3 v = normalize(vec3(-vertexIn.position));
	vec3 r = reflect(-s, n);
	vec3 diffuseLight = diffuseKoefficient * max(dot(s, n), 0.0);
	vec3 Ks = texture(specularMap, vertexIn.tex_coords).rgb;
	float shinyPower = 2000.0f;
	vec3 Ka = vec3(0.2, 0.2, 0.2);
	vec3 specularLight = Ks * pow(max(dot(r, v), 0.0), shinyPower);
	return lightIntensity * (Ka + diffuseLight + specularLight);
}

void main () {
	if((closestObjectHit == currentlyDrawingObject))
		fragment_color = texture(baseImage, vertexIn.tex_coords)* vec4(0.1f,1.0f,0.1f,1.0f) * vec4(ads(), 1.0);
	else
		fragment_color = texture(baseImage, vertexIn.tex_coords) * vec4(ads(), 1.0);
}