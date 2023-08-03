#version 330 core

struct DirLight {
	vec3 position;

    vec3 diffuseCol;
    vec3 ambientCol;
    vec3 specularCol;

    float ambientStr;
    float specularStr;

    float shininess;
};

struct PointLight {
	vec3 position;

    vec3 diffuseCol;
    vec3 ambientCol;
    vec3 specularCol;

    float ambientStr;
    float specularStr;

    float shininess;

	float con;
	float lin;
	float quad;
};

struct SpotLight {
	vec3 position;

    vec3 diffuseCol;
    vec3 ambientCol;
    vec3 specularCol;

    float ambientStr;
    float specularStr;

    float shininess;

	vec3 direction;
	float cutOff;
};

out vec4 FragColor;

uniform vec3 cameraPos;

uniform bool hasTexture;
uniform bool hasNormal;

uniform DirLight DLight;
uniform PointLight PLight;
uniform SpotLight SLight;

uniform sampler2D tex0;
uniform sampler2D normTex;

in vec3 normCoord;
in vec3 fragPos;
in vec2 texCoord;
in mat3 TBN;

vec4 calcDirLight(DirLight Light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-Light.position);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * Light.diffuseCol;

	vec3 ambient = Light.ambientCol * Light.ambientStr;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.1), Light.shininess);
	vec3 specular = spec * Light.specularStr * Light.specularCol;

	return vec4(specular + diffuse + ambient, 1.0);
}

vec4 calcPointLight(PointLight Light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(Light.position - fragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * Light.diffuseCol;

	vec3 ambient = Light.ambientCol * Light.ambientStr;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.1), Light.shininess);
	vec3 specular = spec * Light.specularStr * Light.specularCol;

	float distance = length(Light.position - fragPos);
	float attenuation = 1.0 / (Light.con + Light.lin * distance + Light.quad * pow(distance, 2));

	specular *= attenuation;
	diffuse *= attenuation;
	ambient *= attenuation;

	return vec4(specular + diffuse + ambient, 1.0);
}

void main() {
	vec4 pixelColor = texture(tex0, texCoord);
	if(pixelColor.a < 0.1) discard;


	vec3 normal;
	if (hasNormal) {
		normal = texture(normTex, texCoord).rgb;
		normal = normalize(normal * 2.0 - 1.0);
		normal = normalize(TBN * normal);
	}
	else normal = normalize(normCoord);


	vec3 viewDir = normalize(cameraPos - fragPos);

	vec4 lighting = vec4(1.0);
	//int i = 0;
	//while(PLights[i] != NULL) {
	//}

	lighting =
		calcPointLight(PLight, normal, viewDir) +
		calcDirLight(DLight, normal, viewDir);

	if (hasTexture) FragColor = lighting * texture(tex0, texCoord);
	else FragColor = lighting * vec4(1.0, 0.0, 1.0, 1.0);
}