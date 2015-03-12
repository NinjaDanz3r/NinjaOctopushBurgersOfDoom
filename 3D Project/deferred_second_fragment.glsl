/*
Lighting pass fragment shader (second pass)
*/
#version 400

uniform sampler2D tShadowMap;
uniform sampler2D tPosition;
uniform sampler2D tDiffuse; 
uniform sampler2D tNormals;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;
uniform mat4 lightModelMatrix;
uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;
uniform vec2 screenSize;

out vec4 fragment_color;

const float EPSILON = 0.00001;

// Calculate shadow
float calculateShadow(vec4 lightSpacePosition) {
	vec3 projectedCoords = lightSpacePosition.xyz / lightSpacePosition.w;
	vec2 uvCoords;
	uvCoords.x = 0.5 * projectedCoords.x + 0.5;
	uvCoords.y = 0.5 * projectedCoords.y + 0.5;
	float depth = texture(tShadowMap, uvCoords).x;
	float uvZ = 0.5* projectedCoords.z + 0.5;

	if (depth < uvZ + EPSILON)
		return 1.0;
	else
		return 0.5;
}

//Calculate texcoord
vec2 calculateTexCoord() {
	return gl_FragCoord.xy / screenSize;
}

// Ambient, diffuse and specular lighting.
vec3 ads(vec3 normal, vec3 position) {
	vec4 lightSpacePos = lightViewMatrix * lightProjectionMatrix * lightModelMatrix * vec4(position, 1.0);
	vec3 lightDirection = normalize(vec3(lightPosition) - position);
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(-lightDirection, normal);
	vec3 diffuseLight = diffuseKoefficient * max(dot(lightDirection, normal), 0.0);
	vec3 Ks = vec3(1.0, 1.0, 1.0);
	float shinyPower = 2000.0f;
	vec3 Ka = vec3(0.2, 0.2, 0.2);
	vec3 specularLight = Ks * pow(max(dot(r, v), 0.0), shinyPower);
	return lightIntensity * (Ka + calculateShadow(lightSpacePos) * (diffuseLight + specularLight));
}

void main () {
	vec2 texCoord = calculateTexCoord();
	vec3 position = texture(tPosition, texCoord).xyz;
	vec3 diffuse = texture(tDiffuse, texCoord).xyz;
	vec3 normal = texture(tNormals, texCoord).xyz;

	fragment_color = vec4(diffuse, 1.0) * vec4(ads(normal, position), 1.0);
}