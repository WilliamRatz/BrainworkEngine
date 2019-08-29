#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
	mat4 lightView [16];
	int lightsCount;

	vec4 groundColor;
}ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec4 fragWorldPos;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragNormal;


void main() {
	fragWorldPos = ubo.model * vec4(inPosition, 1.0);
    gl_Position = ubo.proj * ubo.view * fragWorldPos;

    fragColor = ubo.groundColor.xyz;
	fragTexCoord = inTexCoord;
	fragNormal = mat3(ubo.model) * inNormal;
}