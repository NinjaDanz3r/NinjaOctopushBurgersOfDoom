/*
Light pass fragment shader (second pass)
*/
#version 400
in vec2 tex_coords;

uniform sampler2D tDiffuse; 
uniform sampler2D tPosition;
uniform sampler2D tNormals;
uniform sampler2D baseImage;
uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;

out vec4 fragment_color;

// Ambient, diffuse and specular lighting.
vec3 ads() {
	vec4 image = texture( tDiffuse, tex_coords );
	vec4 position = texture( tPosition, tex_coords );
	vec4 normal = texture( tNormals, tex_coords );

	vec3 n = normalize(normal);
	vec3 s = normalize(vec3(lightPosition) - position);
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(-s, n);
	vec3 diffuseLight = diffuseKoefficient * max(dot(s, n), 0.0);
	vec3 Ks = vec3(1.0, 1.0, 1.0);
	float shinyPower = 2000.0f;
	vec3 Ka = vec3(0.2, 0.2, 0.2);
	vec3 specularLight = Ks * pow(max(dot(r, v), 0.0), shinyPower);
	return lightIntensity * (Ka + diffuseLight + specularLight);
}

void main () {
	fragment_color = texture(baseImage, tex_coords) * vec4(ads(), 1.0);
}