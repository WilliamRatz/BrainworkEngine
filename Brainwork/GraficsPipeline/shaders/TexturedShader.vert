#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;

	vec4 groundColor;
}ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;


void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);

    fragColor = ubo.groundColor.xyz;
	fragTexCoord = inTexCoord;
}



/*
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
	vec4 lightPos;
	vec4 lightColor;
	vec4 groundColor;
}ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec3 fragViewVec;
layout(location = 4) out vec3 fragLightVec;
layout(location = 5) out vec3 fragLightColor;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
	vec4 worldPos = ubo.model * vec4(inPosition, 1.0);

    fragColor = ubo.groundColor.xyz;
    fragTexCoord = inTexCoord;
    fragNormal = mat3(ubo.model) * inNormal;
	fragViewVec = (ubo.view * worldPos).xyz;
	fragLightVec = ubo.lightPos.xyz - vec3(worldPos);
	fragLightColor = ubo.lightColor.xyz;
}
*/