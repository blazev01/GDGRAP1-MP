#version 330 core

struct Light {
	vec3 position;

    vec3 diffuseCol;
    vec3 ambientCol;
    vec3 specularCol;

    float ambientStr;
    float specularStr;

    float shininess;
};

struct PointLight {
	Light Base;

	float con;
	float lin;
	float quad;
};

struct SpotLight {
	Light Base;

	vec3 direction;
	float cutOff;
};

out vec4 FragColor;

uniform vec3 cameraPos;

uniform Light DLights[5];
uniform PointLight PLights[5];
uniform SpotLight SLights[5];

uniform vec3 lightPos;
uniform vec3 diffuseColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform float specularStr;
uniform vec3 specularColor;

uniform float shininess;

uniform sampler2D tex0;

in vec3 normCoord;
in vec3 fragPos;
in vec2 texCoord;

vec4 calcDirLight(vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-lightPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * diffuseColor;

	vec3 ambient = ambientColor * ambientStr;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.1), shininess);
	vec3 specular = spec * specularStr * specularColor;

	return vec4(specular + diffuse + ambient, 1.0);
}

vec4 calcPointLight(vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(lightPos - fragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * diffuseColor;

	vec3 ambient = ambientColor * ambientStr;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.1), shininess);
	vec3 specular = spec * specularStr * specularColor;

	float con = 1.0;
	float lin = 0.02;
	float quad = 0.0015;

	float distance = length(lightPos - fragPos);
	float attenuation = 1.0 / (con + lin * distance + quad * pow(distance, 2));

	specular *= attenuation;
	diffuse *= attenuation;
	ambient *= attenuation;

	return vec4(specular + diffuse + ambient, 1.0);
}

void main() {
	vec3 normal = normalize(normCoord);
	vec3 viewDir = normalize(cameraPos - fragPos);

	vec4 lighting = vec4(1.0);
	//int i = 0;
	//while(PLights[i] != NULL) {
	//}

	lighting = calcPointLight(normal, viewDir);

	FragColor = lighting * texture(tex0, texCoord);
}