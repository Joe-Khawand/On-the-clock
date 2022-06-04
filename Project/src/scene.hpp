#pragma once

#include "cgp/cgp.hpp"
#include "gui_helper.hpp" // not sure whether that's necessary 
#include "scenes/main_scene/main_scene.hpp"
#include "scenes/basket_scene.hpp"
#include "scenes/initial_scene.hpp"

// The structure of the custom scene
struct scene_structure {

	// TODO does this stay here?
	bool init;
	float t_init;
	float dt_init;
	cgp::timer_basic timer_init;
	bool click;

	scene_environment_with_multiple_lights environment; // The specific scene environment with multiple lights (*)

	main_scene_structure main_environment;
	basket_scene_structure basket_environment;
	initial_scene_structure initial_environment;
	// Booleans used to decide which scene to display
	bool initial_scene;
	bool main_scene;
	bool basket_scene;
	bool transition;

	// TODO does this stay here?
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                       // Standard GUI element storage

	// TODO does this stay here?
	// Timers used for the animation
	cgp::timer_basic timer;
	float dt;

	// TODO does this stay here? (yes)
	// Flight
	cgp::timer_basic flight_timer;//independent timer for flight
	float flight_speed = 0.0f;//modifiable flight speed

	// Objects used to display text messages on the screen
	cgp::mesh_drawable text;
	bool display_text;
	float time_text_appeared;

	// ****************************** //
	// Functions
	// ****************************** //

	// Function to call in the animation loop in main (*)
	// This function replace the standard trackball behavior that must also be removed in the main (from mouse_move_callback)
	void update_camera(); 
	void mouse_click(); // To activate nexus

	void initialize();

	void display();
	void display_gui();
	void display_text_billboard();
} displayed_scene;

