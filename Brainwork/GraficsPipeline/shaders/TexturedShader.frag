#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
	mat4 lightView;

	vec4 groundColor;
}ubo;


layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform sampler2D lightDepthSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec4 fragWorldPos;


layout(location = 0) out vec4 outColor;

void main() {
	
	vec4 posFromLight = ubo.proj * ubo.lightView * fragWorldPos;
	posFromLight.xyzw /= posFromLight.w;

	posFromLight.xy = posFromLight.xy * 0.5 + 0.5;

	float lightIntensity = 1.f;
	if((posFromLight.y > 0) && (posFromLight.y < 1)&&
	   (posFromLight.x > 0) && (posFromLight.x < 1) )
	{
		float depthLight = texture(lightDepthSampler, posFromLight.xy).x;

		lightIntensity = (depthLight + 0.01 <posFromLight.z) ? 0:1;
		lightIntensity = smoothstep(posFromLight.z-0.01, posFromLight.z+0.01, depthLight + 0.01);
	}

	outColor = (texture(texSampler, fragTexCoord) * vec4(fragColor, 1.0)) * (lightIntensity*0.8+0.2);
	
}




















/*
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 fragViewVec;
layout(location = 4) in vec3 fragLightVec;
layout(location = 5) in vec3 fragLightColor;


layout(location = 0) out vec4 outColor;

void main() {
    //outColor = texture(texSampler, fragTexCoord) * vec4(fragColor, 1.0);
	vec3 N = normalize(fragNormal);
	vec3 L = normalize(fragLightVec);
	vec3 V = normalize(fragViewVec);
	vec3 R = reflect(L,N);

	vec3 ambient = fragColor * 0.1;
	vec3 diffuse = max(dot(N,L), 0.0) * fragColor;
	vec3 specular = (pow(max(dot(R,V), 0.0), 16.0) * vec3(1.35)) * fragLightColor;
	
	outColor = vec4(ambient + diffuse + specular, 1.0);
}
*/