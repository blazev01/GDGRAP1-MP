#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTex;
layout(location = 3) in vec3 mTan;
layout(location = 4) in vec3 mBtan;

out vec3 normCoord;
out vec3 fragPos;
out vec2 texCoord;
out mat3 TBN;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * transform * vec4(aPos, 1.0);

	mat3 modelMat = mat3(transpose(inverse(transform)));

	normCoord = modelMat * vertexNormal;
	fragPos = vec3(transform * vec4(aPos, 1.0));

	texCoord = aTex;

	vec3 T = normalize(modelMat * mTan);
	vec3 B = normalize(modelMat * mBtan);
	vec3 N = normalize(normCoord);

	TBN = mat3(T, B, N);
}