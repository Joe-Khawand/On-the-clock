#version 330 core

in struct fragment_data
{
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 uv;

	vec3 eye;
} fragment;

layout(location=0) out vec4 FragColor;

uniform sampler2D image_texture;

uniform vec3 light = vec3(1.0, 1.0, 1.0);

uniform vec3 color = vec3(1.0, 1.0, 1.0); // Unifor color of the object
uniform float alpha = 1.0f; // alpha coefficient
uniform float Ka = 0.4; // Ambient coefficient
uniform float Kd = 0.8; // Diffuse coefficient
uniform float Ks = 0.4f;// Specular coefficient
uniform float specular_exp = 64.0; // Specular exponent
uniform bool use_texture = true;
uniform bool texture_inverse_y = false;

uniform vec3 spotlight_color[5];
uniform vec3 spotlight_position[5];
uniform float spotlight_falloff;
uniform float fog_falloff;

void main()
{
	vec3 N = normalize(fragment.normal);
	if (gl_FrontFacing == false) {
		N = -N;
	}
	vec2 uv_image = vec2(fragment.uv.x, 1.0-fragment.uv.y);
	if(texture_inverse_y) {
		uv_image.y = 1.0-uv_image.y;
	}
	vec4 color_image_texture = texture(image_texture, uv_image);
	if(use_texture==false) {
		color_image_texture=vec4(1.0,1.0,1.0,1.0);
	}

	vec3 color_shading = vec3(1,1,1);

    //fog effect
	float depth = length(fragment.eye-fragment.position);
	float w_depth = exp(-fog_falloff*depth*depth + 0.0 * spotlight_falloff);
	vec3 color_with_fog = w_depth*color_shading+(1-w_depth)*vec3(0,0,0); //w_depth*color_shading+(1-w_depth)*vec3(0.7,0.7,0.7);

	FragColor = vec4( color_with_fog, alpha * color_image_texture.a);
}
