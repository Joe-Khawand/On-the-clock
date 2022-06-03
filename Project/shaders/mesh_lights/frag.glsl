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

uniform vec3 color = vec3(1, 1, 1); // Unifor color of the object
uniform float alpha = 1.0f; // alpha coefficient
uniform float Ka = 0.0000001; // Ambient coefficient
uniform float Kd = 0.8; // Diffuse coefficient
uniform float Ks = 0.4f;// Specular coefficient
uniform float specular_exp = 64.0; // Specular exponent
uniform bool use_texture = true;
uniform bool texture_inverse_y = false;

uniform vec3 spotlight_color[13];
uniform vec3 spotlight_position[13];
uniform float spotlight_falloff;
uniform float fog_falloff;
uniform int N_spotlight;
uniform int colors_displayed;
uniform vec4 activation_colors;
uniform float time;

void main()
{
	// Determines which colors/textures to display
	float dist_to_center = length(fragment.position);
	bool not_reached = true;
	int nb_colors = min(colors_displayed, 4);
	while(nb_colors > 0 && not_reached) {
		float time_activated;
		if (nb_colors==1)
			time_activated = activation_colors.r;
		if (nb_colors==2)
			time_activated = activation_colors.b;
		if (nb_colors==3)
			time_activated = activation_colors.g;
		if (nb_colors==4)
			time_activated = activation_colors.a; // textures
		if ((time - time_activated)*50 > dist_to_center)
			not_reached = false;
		else
			nb_colors -= 1;
	}
	
	vec3 N = normalize(fragment.normal);
	if (gl_FrontFacing == false) {
		N = -N;
	}
	vec2 uv_image = vec2(fragment.uv.r, 1.0-fragment.uv.y);
	if(texture_inverse_y) {
		uv_image.y = 1.0-uv_image.y;
	}
	vec4 color_image_texture = texture(image_texture, uv_image);
	if(use_texture==false || nb_colors<4) {
		color_image_texture=vec4(1.0,1.0,1.0,1.0);
	}

	vec3 color_object  = fragment.color * color * color_image_texture.rgb;
	
	if(nb_colors==0) {
		color_object = (color_object.rrr + color_object.ggg + color_object.bbb) / 6.0;
	}
	if(nb_colors==1) {
		float red = (4 * color_object.r + color_object.g + color_object.b) / 6.0;
		float green = (color_object.r + color_object.g + color_object.b) / 6.0;
		float blue = (color_object.r + color_object.g + color_object.b) / 6.0;
		color_object = vec3(red, green, blue);
	}
	if(nb_colors==2) {
		float red = (4 * color_object.r + color_object.g) / 5.0;
		float green = (color_object.r + color_object.g + color_object.b) / 5.0;
		float blue = (4 * color_object.b + color_object.g) / 5.0;
		color_object = vec3(red, green, blue);
	}


	//float Ka = 0.1;
	vec3 color_shading = 0 * color_object;

	color_shading += 0.3 * max(dot(N, normalize(vec3(10.0, 5.0, 3.0))), 0.) * vec3(1, 0.8, 0.8);


	for(int k_light=0; k_light<N_spotlight; k_light++)
	{
		vec3 v = spotlight_position[k_light]-fragment.position;
		float dist = length(v);
		vec3 L = normalize(v);
		float diffuse = max(dot(N,L),0.0);
		float specular = 0.0;
		if(diffuse>0.0){
			vec3 R = reflect(-L,N);
			vec3 V = normalize(fragment.eye-fragment.position);
			specular = pow( max(dot(R,V),0.0), specular_exp );
		}
		
		// spotlight color
		color_shading += (Kd*diffuse*color_object + Ks * specular)*spotlight_color[k_light]*exp(-spotlight_falloff*dist*dist);
	}

    //fog effect
	float depth = length(fragment.eye-fragment.position);
	float w_depth = exp(-fog_falloff*depth*depth);
	vec3 color_with_fog = w_depth*color_shading+(1-w_depth)*vec3(0,0,0); //w_depth*color_shading+(1-w_depth)*vec3(0.7,0.7,0.7);
	if (fragment.position.z < -150)
		color_with_fog = color_with_fog * (fragment.position.z + 200) / 50;

	FragColor = vec4( color_with_fog, alpha * color_image_texture.a);
}
