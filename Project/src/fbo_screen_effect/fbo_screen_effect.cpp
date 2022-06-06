#include "fbo_screen_effect.hpp"

using namespace cgp;

void fbo_screen_effect::initialize(GLuint shader_screen_effect, int width, int height)
{
	window_width  = width;
	window_height = height;

	// Allocate texture to store a rendered image
	glGenTextures(1, &output_texture_id);
	glBindTexture(GL_TEXTURE_2D, output_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Allocate a depth buffer - need to do it when using the frame buffer
	int const max_window_width = 2000;
	int const max_window_height = 2000;
	glGenRenderbuffers(1, &depth_buffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, max_window_width, max_window_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Create frame buffer
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	// associate the texture to the frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, output_texture_id, 0);
	// associate the depth-buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);

	// Reset the standard framebuffer to output on the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	// The result of the second pass is displayed on a quad
	quad_screen.initialize(mesh_primitive_quadrangle({ -1,-1,0 }, { 1,-1,0 }, { 1,1,0 }, { -1,1,0 }));
	quad_screen.texture = output_texture_id;
	quad_screen.shader = shader_screen_effect;

}

void fbo_screen_effect::update_screen_resize(int width, int height)
{
	window_width  = width;
	window_height = height;

	glBindTexture(GL_TEXTURE_2D, output_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void fbo_screen_effect::prepare_render_pass_into_fbo(vec3 const& background_color)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, window_width, window_height);
	glBindTexture(GL_TEXTURE_2D, output_texture_id);

	glClearColor(background_color.x, background_color.y, background_color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}


void draw_effect(fbo_screen_effect const& screen_effect)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screen_effect.window_width, screen_effect.window_height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	mesh_drawable const& drawable = screen_effect.quad_screen;
	if (drawable.number_triangles == 0) return;

	// Setup shader
	assert_cgp(drawable.shader != 0, "Try to draw mesh_drawable without shader [name:" + drawable.name + "]");
	assert_cgp(drawable.texture != 0, "Try to draw mesh_drawable without texture [name:" + drawable.name + "]");
	glUseProgram(drawable.shader); opengl_check;

	// Set texture
	glActiveTexture(GL_TEXTURE0); opengl_check;
	glBindTexture(GL_TEXTURE_2D, drawable.texture); opengl_check;
	opengl_uniform(drawable.shader, "image_texture", 0);  opengl_check;

	// Call draw function
	assert_cgp(drawable.number_triangles > 0, "Try to draw mesh_drawable with 0 triangles [name:" + drawable.name + "]"); opengl_check;
	glBindVertexArray(drawable.vao);   opengl_check;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.vbo.at("index")); opengl_check;
	glDrawElements(GL_TRIANGLES, GLsizei(drawable.number_triangles * 3), GL_UNSIGNED_INT, nullptr); opengl_check;

	// Clean buffers
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}