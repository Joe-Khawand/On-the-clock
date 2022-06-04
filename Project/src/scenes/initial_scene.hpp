#pragma once

#include "cgp/cgp.hpp"
#include "gui_helper.hpp"
#include "scenes/main_scene/multiple_lights/multiple_lights.hpp" 

// The structure of the custom scene
struct initial_scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	//elements de la premiere scene
	bool init;
	float t_init;
	float dt_init;
	cgp::timer_basic timer_init;
	bool click;

	//cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	scene_environment_with_multiple_lights environment; // The specific scene environment with multiple lights (*)
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                       // Standard GUI element storage

	cgp::skybox_drawable bright_skybox;
    cgp::mesh_drawable initial_scene_drawable;
    cgp::mesh_drawable clock_drawable;

	// Timers used for the animation
	cgp::timer_basic timer;
	float dt;

	// ****************************** //
	// Functions
	// ****************************** //

	void update_camera(); 
	void mouse_click();

	void initialize_initial_scene();  // Standard initialization to be called before the animation loop

	void display_initial_scene();     // The frame display to be called within the animation loop
};

