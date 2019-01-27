#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform LightInfoObject {
    mat4 model;
    mat4 lightView;
    mat4 proj;

	vec4 groundColor;
}lio;

layout(location = 0) in vec3 inPosition;


void main() {
    gl_Position = lio.proj * lio.lightView * lio.model * vec4(inPosition, 1.0);
    
}