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


layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform sampler2D lightDepthSampler[16];

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec4 fragWorldPos;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

void main() {

	float lightIntensity = 1.f;

for(int i = 0; i < ubo.lightsCount; ++i)
{
	vec4 posFromLight = ubo.proj * ubo.lightView[i] * fragWorldPos;
	posFromLight.xyzw /= posFromLight.w;

	posFromLight.xy = posFromLight.xy * 0.5 + 0.5;

	if((posFromLight.y > 0) && (posFromLight.y < 1)&&
	   (posFromLight.x > 0) && (posFromLight.x < 1) )
	{
		float depthLight = texture(lightDepthSampler[i], posFromLight.xy).x;

		lightIntensity *= smoothstep(posFromLight.z-0.01, posFromLight.z+0.01, depthLight + 0.01);
	}
}
	outColor = (texture(texSampler, fragTexCoord) * vec4(fragColor, 1.0)) * (lightIntensity*0.8+0.2);
	
}

