/*
Lighting pass fragment shader (second pass)
*/
#version 400

uniform sampler2D tPosition;
uniform sampler2D tDiffuse; 
uniform sampler2D tNormals;
uniform sampler2D tSpecular;
uniform sampler2D tDepth;
uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;
uniform vec2 screenSize;

out vec4 fragment_color;

// Calculate texcoord
vec2 calculateTexCoord() {
	return gl_FragCoord.xy / screenSize;
}

// Ambient, diffuse and specular lighting.
vec3 ads(vec3 normal, vec3 position, vec3 specular) {
	vec3 lightDirection = normalize(vec3(lightPosition) - position);
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(-lightDirection, normal);
	vec3 diffuseLight = diffuseKoefficient * max(dot(lightDirection, normal), 0.0);
	float shinyPower = 2000.0f;
	vec3 Ka = vec3(0.2, 0.2, 0.2);
	vec3 specularLight = specular * pow(max(dot(r, v), 0.0), shinyPower);
	return lightIntensity * (Ka + diffuseLight + specularLight);
}

void main () {
	vec2 texCoord = calculateTexCoord();
	vec3 position = texture(tPosition, texCoord).xyz;
	vec3 diffuse = texture(tDiffuse, texCoord).rgb;
	vec3 normal = texture(tNormals, texCoord).xyz;
	vec3 specular = texture(tSpecular, texCoord).xyz;
	
	fragment_color = vec4(diffuse, 1.0) * vec4(ads(normal, position, specular), 1.0);
	gl_FragDepth = texture(tDepth, texCoord).r;
}