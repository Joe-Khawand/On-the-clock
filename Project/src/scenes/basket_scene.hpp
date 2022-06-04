#pragma once

#include "cgp/cgp.hpp"
#include "gui_helper.hpp"
#include "multiple_lights/multiple_lights.hpp" 

// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	//elements de la premiere scene
	bool init;
	float t_init;
	float dt_init;
	cgp::timer_basic timer_init;
	bool click;

	//elements scene basket
	bool basket_scene;
	bool transition;

	//cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	scene_environment_with_multiple_lights environment; // The specific scene environment with multiple lights (*)
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                       // Standard GUI element storage

	cgp::skybox_drawable bright_skybox;

	// Timers used for the animation
	cgp::timer_basic timer;
	float dt;

	// Flight
	cgp::timer_basic flight_timer;//independent timer for flight
	float flight_speed = 0.0f;//modifiable flight speed

	cgp::mesh_drawable text;
	bool display_text;
	float time_text_appeared;

	// ****************************** //
	// Functions
	// ****************************** //

	void update_camera(); 
	void mouse_click();

	void initialize();  // Standard initialization to be called before the animation loop

	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};

