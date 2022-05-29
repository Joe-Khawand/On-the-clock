#include "multiple_lights.hpp"

using namespace cgp;

void opengl_uniform(GLuint shader, scene_environment_with_multiple_lights const& environment)
{
	// Send the default uniforms from the basic scene_environment
	opengl_uniform(shader, scene_environment_basic(environment));

	// Send the position and color of sphere as uniforms
	/** Note: Here we use the raw OpenGL call to glUniform3fv allowing us to pass a vector of data (here an array of 5 positions and 5 colors) */
	int const N_spotlight = environment.spotlight_color.max_size();
	GLint const location_color = glGetUniformLocation(shader, "spotlight_color");
	GLint const location_position = glGetUniformLocation(shader, "spotlight_position");
	glUniform3fv(location_color, N_spotlight, ptr(environment.spotlight_color[0]));
	glUniform3fv(location_position, N_spotlight, ptr(environment.spotlight_position[0]));
		
	// Send the falloff values as uniforms
	opengl_uniform(shader, "spotlight_falloff", environment.spotlight_falloff);
	opengl_uniform(shader, "fog_falloff", environment.fog_falloff);
	opengl_uniform(shader, "projection", environment.projection.matrix());
	opengl_uniform(shader, "view", environment.camera.matrix_view());
}

void compute_light_position(float t, scene_environment_with_multiple_lights& environment)
{
	// Adapt the position and color of the spotlight procedurally as a function of t

	// Central nexus core
	environment.spotlight_position[0] = {0, 0, 0};
	
	for (int i=1; i<n_lights; i++) {
		environment.spotlight_position[i] = {125 * std::cos(i * M_PI / 6), - 125 * std::sin(i * M_PI / 6), -30};
	}
}

void display_gui_falloff(scene_environment_with_multiple_lights& environment)
{
	ImGui::SliderFloat("Light falloff", &environment.spotlight_falloff, 0, 0.01f, "%0.6f", 2.0f);
	ImGui::SliderFloat("Fog falloff", &environment.fog_falloff, 0, 0.001f, "%0.7f", 2.0f);
}

scene_environment_with_multiple_lights::scene_environment_with_multiple_lights()
{
 	projection = camera_projection::perspective(50.0f * Pi / 180, 1.0f, 0.1f, 500.0f);
}