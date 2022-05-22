#pragma once

#include "cgp/cgp.hpp"
#include "cgp/helper_common_scene/helper_common_scene.hpp"

/** Scene environment that adds the following uniform parameters to be sent to the shader in shaders/mesh_lights/
* - 5 lights (spotlight model) defined by a position and a color
* - An attenuation of the light along the distance (global for all the 5 lights)
* - A fog effect with parametric falloff distance
* 
* Note: If you want a different number of lights, you will need to change the size of the array in the scene but also uniform parameters in the vertex shader.
*/
const int n_lights = 5;

struct scene_environment_with_multiple_lights : cgp::scene_environment_basic
{
	// Store position for 5 lights
	std::array<cgp::vec3, n_lights> spotlight_position;
	// The (r,g,b) color of the 5 lights
	std::array<cgp::vec3, n_lights> spotlight_color;

	// The characteristic attenuation of the light
	float spotlight_falloff = 0.0003f;

	// The characteristic attenuation due to the fog
	float fog_falloff = 0.0001f;

	// Standard parameters (same as basic environment)
	cgp::vec3 background_color;
	cgp::camera_projection projection;

	// Change the standard rotating camera to a "head camera" more appropriate to model free-flight (*)
	cgp::camera_spherical_coordinates camera;

	scene_environment_with_multiple_lights();
};

// Send the uniform parameters of the scene with light - Function automatically called when using draw([mesh_drawable], scene_environment_with_multiple_lights);
void opengl_uniform(GLuint shader, scene_environment_with_multiple_lights const& environment);

// Function to call in the display function of your scene
//  Compute a new position and color of the lights procedurally.
//  This function can be modified at your will.
void compute_light_position(float t, scene_environment_with_multiple_lights& environment);

/** A structure to help drawing the light as sphere
* The spotlights are simply displayed as spheres */
struct light_shape_drawable
{
	cgp::mesh_drawable spotlight_sphere;              // a mesh_drawable of a sphere
	void initialize(GLuint shader_multiple_lights);   // Initialise the spotlight_sphere to a sphere
};
// Function to call in your scene display to draw all the spotlights
void draw(light_shape_drawable lights, scene_environment_with_multiple_lights const& environment);

// Function to call in your display_gui to add the sliders modifying the spotlight and fog falloff
void display_gui_falloff(scene_environment_with_multiple_lights& environment);

