#pragma once

#include "cgp/cgp.hpp"

struct fbo_screen_effect
{
	GLuint fbo;
	GLuint output_texture_id;
	GLuint depth_buffer_id;

	cgp::mesh_drawable quad_screen;

	int window_width;
	int window_height;

	void initialize(GLuint shader_screen_effect, int width, int height);
	void update_screen_resize(int width, int height); // Function to call everytime the window is resized

	void prepare_render_pass_into_fbo(cgp::vec3 const& background_color = { 0,0,0 });
};

void draw_effect(fbo_screen_effect const& screen_effect);