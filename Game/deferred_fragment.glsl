/*
Lighting pass fragment shader (second pass)
*/
#version 400

uniform sampler2D tShadowMap;
uniform sampler2D tPosition;
uniform sampler2D tDiffuse; 
uniform sampler2D tNormals;
uniform sampler2D tSpecular;
uniform sampler2D tDepth;

uniform mat4 UVtransformMatrix;
uniform mat4 inverseViewMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;

uniform vec4 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 diffuseKoefficient;
uniform vec2 screenSize;

out vec4 fragment_color;



const float EPSILON = 0.03;

float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}
// Calculate shadow
float calculateShadow(vec4 lightSpacePosition, vec4 worldPosition) {

vec2 poisson[15] = vec2[](
	vec2( 0.3717325, 0.1279892),
	vec2(0.4879754, -0.3658713),
	vec2(0.794171, 0.3522189),
	vec2(0.3074657, 0.6046221),
	vec2(-0.1719546, 0.1717038),
	vec2(0.8643684, -0.07669879),
	vec2(-0.3394284, -0.2177678),
	vec2(0.07109351, -0.4859956),
	vec2(0.4489738, -0.7939949),
	vec2(-0.1399191, -0.8488325),
	vec2(-0.6998154, -0.5012075),
	vec2(-0.08893247, 0.9369829),
	vec2(-0.4376774, 0.5030558),
	vec2(-0.9372669, 0.04219909),
	vec2(-0.8517231, 0.4333114)
);

    vec4 shadowCoord= UVtransformMatrix * lightSpacePosition;
	float visibility = 1.0;
    //float visibility = texture( tShadowMap, vec3(shadowCoord.xy,(shadowCoord.z)/shadowCoord.w));
	for (int i=0;i<4;i++){
		if ( texture( tShadowMap, (shadowCoord.xy/shadowCoord.w) + poisson[i]/700.0 ).z  <  (shadowCoord.z-EPSILON)/shadowCoord.w ){
			visibility-=1.0/5.0;
		 }
		 /*int index = int(15.0*random(floor(worldPosition.xyz*1000.0), i))%15;
		 if ( texture( tShadowMap, (shadowCoord.xy/shadowCoord.w) + poisson[index]/700.0 ).z  <  (shadowCoord.z-EPSILON)/shadowCoord.w ){
			visibility-=0.2;
		 }*/
		 //visibility -= 0.2*(1.0-texture( tShadowMap, vec3(shadowCoord.xy + poisson[index]/700.0,  (shadowCoord.z-EPSILON)/shadowCoord.w) ));
	}
    return visibility;
}

//Calculate texcoord
vec2 calculateTexCoord() {
	return gl_FragCoord.xy / screenSize;
}

// Ambient, diffuse and specular lighting.
vec3 ads(vec3 normal, vec3 position, vec3 specular) {
	vec4 worldPos = inverseViewMatrix * vec4(position, 1.0);
	vec4 lightSpacePos = lightProjectionMatrix * lightViewMatrix * worldPos;
	float visibility = calculateShadow(lightSpacePos, worldPos);
	vec3 lightDirection = normalize(vec3(lightPosition) - position);
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(-lightDirection, normal)* ((visibility*2) -1.0);
	vec3 diffuseLight = diffuseKoefficient * max(dot(lightDirection, normal), 0.0);
	float shinyPower = 2000.0f;
	vec3 Ka = vec3(0.2, 0.2, 0.2);
	vec3 specularLight = specular * pow(max(dot(r, v), 0.0), shinyPower);
	return lightIntensity * (Ka + visibility*(diffuseLight + specularLight));
	//return lightIntensity * (Ka + diffuseLight + specularLight);
    //return vec3(calculateShadow(lightSpacePos), calculateShadow(lightSpacePos), calculateShadow(lightSpacePos));
}

void main () {
	vec2 texCoord = calculateTexCoord();
	vec3 position = texture(tPosition, texCoord).xyz;
	vec3 diffuse = texture(tDiffuse, texCoord).rgb;
	vec3 normal = texture(tNormals, texCoord).xyz;
	vec3 specular = texture(tSpecular, texCoord).xyz;
	
	//fragment_color = vec4(ads(normal, position, specular), 1.0);
	fragment_color = vec4(diffuse, 1.0) * vec4(ads(normal, position, specular), 1.0);
	gl_FragDepth = texture(tDepth, texCoord).r;
}