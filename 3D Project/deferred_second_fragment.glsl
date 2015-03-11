/*
Lighting pass fragment shader (second pass)
*/
#version 400

uniform samplerCube tShadowMap;
uniform sampler2D tPosition;
uniform sampler2D tDiffuse; 
uniform sampler2D tNormals;
uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;
uniform vec2 screenSize;

#define epsilon 0.00001;

out vec4 fragment_color;

// Calculate shadow, Använd nedan(när shadowmap finns)
float calculateShadow(vec3 lightDirection) {
	float sampleDistance = texture(tShadowMap, lightDirection).r;
	float distance = length(lightDirection);

	if (distance <= (sampleDistance + epsilon))//WHY U NO WORK.
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
	vec3 lightDirection = normalize(vec3(lightPosition) - position);
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(-lightDirection, normal);
	vec3 diffuseLight = diffuseKoefficient * max(dot(lightDirection, normal), 0.0);
	vec3 Ks = vec3(1.0, 1.0, 1.0);
	float shinyPower = 2000.0f;
	vec3 Ka = vec3(0.2, 0.2, 0.2);
	vec3 specularLight = Ks * pow(max(dot(r, v), 0.0), shinyPower);
	return lightIntensity * (Ka + diffuseLight + specularLight);
}

void main () {
	vec2 texCoord = calculateTexCoord();
	vec3 position = texture(tPosition, texCoord).xyz;
	vec3 diffuse = texture(tDiffuse, texCoord).xyz;
	vec3 normal = texture(tNormals, texCoord).xyz;

	fragment_color = vec4(diffuse, 1.0) * vec4(ads(normal, position), 1.0);
}