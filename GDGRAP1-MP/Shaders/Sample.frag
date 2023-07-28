#version 330 core

out vec4 FragColor; //Color pixel

uniform vec3 lightPos;
uniform vec3 diffuseColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specularStr;
uniform vec3 specularColor;
uniform float shininess;

uniform sampler2D tex0;
uniform sampler2D normTex;

in vec3 normCoord;
in vec3 fragPos;
in vec2 texCoord;
in mat3 TBN;

void main() {
	//               r     g     b     a     0-1
	// FragColor = vec4(1.0f, 0.7f, 0.8f, 1.0f);

	//get color of pixel
	vec4 pixelColor = texture(tex0, texCoord);
	//if alpha is low enough
	if(pixelColor.a < 0.1) {
	//discard pixel
	discard;
	//ignore the rest after this
	}

	vec3 normal = texture(normTex, texCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

	vec3 lightDir = normalize(lightPos - fragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * diffuseColor;

	vec3 ambient = ambientColor * ambientStr;

	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.1), shininess);
	vec3 specular = spec * specularStr * specularColor;
	
	float con = 1.0;
	float lin = 0.005;
	float quad = 0.0002;

	float distance = length(lightPos - fragPos);
	float attenuation = 1.0 / (con + lin * distance + quad * pow(distance, 2));

	specular *= attenuation;
	diffuse *= attenuation;
	ambient *= attenuation;

	FragColor = vec4(specular + diffuse + ambient, 1.0) * texture(tex0, texCoord);
}