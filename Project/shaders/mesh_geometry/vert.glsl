#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out struct fragment_data
{
    vec3 position;
    vec3 normal;
	vec3 eye;
} fragment;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	fragment.position = vec3(model * vec4(position,1.0));
	fragment.normal   = vec3(model * vec4(normal  ,0.0));
	fragment.eye = vec3(inverse(view)*vec4(0,0,0,1.0));

	gl_Position = projection * view * model * vec4(position, 1.0);
}
