#include "multiple_lights.hpp"

using namespace cgp;

void opengl_uniform(GLuint shader, scene_environment_with_multiple_lights const& environment)
{
	// Send the default uniforms from the basic scene_environment
	opengl_uniform(shader, scene_environment_basic(environment));

	// Send the position and color of sphere as uniforms
	/** Note: Here we use the raw OpenGL call to glUniform3fv allowing us to pass a vector of data (here an array of 5 positions and 5 colors) */
	int const N_spotlight = environment.spotlight_color.size();
	GLint const location_color = glGetUniformLocation(shader, "spotlight_color");
	GLint const location_position = glGetUniformLocation(shader, "spotlight_position");
	glUniform3fv(location_color, N_spotlight, ptr(environment.spotlight_color[0]));
	glUniform3fv(location_position, N_spotlight, ptr(environment.spotlight_position[0]));
		
	// Send the falloff values as uniforms
	opengl_uniform(shader, "spotlight_falloff", environment.spotlight_falloff);
	opengl_uniform(shader, "fog_falloff", environment.fog_falloff);
}

void compute_light_position(float t, scene_environment_with_multiple_lights& environment)
{
	// Adapt the position and color of the spotlight procedurally as a function of t

	// Central nexus core
	environment.spotlight_position[0] = {0, 0, 0};
	environment.spotlight_color[0] = { 1.0f, 0.9f, 0.5f };

	environment.spotlight_position[1] = vec3{-120, 0, 0};
	environment.spotlight_color[1] = { 0.0f, 1.0f, 1.0f };

	environment.spotlight_position[2] = vec3{  2 * cos(3 * t),
						sin(3 * t),
						0.0f};
	environment.spotlight_color[2] = {0,0,0}; //2 * (std::cos(t) + 1.0f) / 2.0 * vec3(1, 1, 1);

	environment.spotlight_position[3] = vec3{15, 10, 0};
	environment.spotlight_color[3] = { 0.0f, 1.0f, 1.0f };

	environment.spotlight_position[4] = vec3{ 3 * cos(3 * t) * cos(3 * t + 17.f),
						1.7 * cos(3 * t)* sin(3 * t + 17.f),
						2.3 * sin(3 * t) };
	environment.spotlight_color[4] = {0,0,0}; //{ 1.0f, 0.9f, 0.5f };
}

void light_shape_drawable::initialize(GLuint shader_multiple_lights)
{
	float const radius_sphere = 0.05f; // Adapt the radius of the spotlight as you wish
	mesh spotlight_sphere_mesh = mesh_primitive_sphere(radius_sphere); // Initialise the spotlight as a sphere
	spotlight_sphere_mesh.flip_connectivity();                 // Flip the normal as the sphere is illuminated from its inside.
	spotlight_sphere.initialize(spotlight_sphere_mesh, "Spotlight Sphere", shader_multiple_lights); // Convert the mesh to a mesh_drawable with the correct shader
}

void draw(light_shape_drawable lights, scene_environment_with_multiple_lights const& environment)
{
	// Display all the spotlight at their position and with their respective color.
	for (size_t k = 0; k < environment.spotlight_position.size(); ++k)
	{
		lights.spotlight_sphere.transform.translation = environment.spotlight_position[k];
		lights.spotlight_sphere.shading.color = environment.spotlight_color[k];
		draw(lights.spotlight_sphere, environment);
	}
}

void display_gui_falloff(scene_environment_with_multiple_lights& environment)
{
	ImGui::SliderFloat("Light falloff", &environment.spotlight_falloff, 0, 0.01f, "%0.4f", 2.0f);
	ImGui::SliderFloat("Fog falloff", &environment.fog_falloff, 0, 0.001f, "%0.5f", 2.0f);
}