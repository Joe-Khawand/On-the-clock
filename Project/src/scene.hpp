#pragma once

#include "cgp/cgp.hpp"
#include "implicit_surface/implicit_surface.hpp"
#include "implicit_surface/field_function.hpp"
#include "gui_helper.hpp"
#include "multiple_lights/multiple_lights.hpp" 
#include "clock_city.hpp"
#include "maze.hpp"

// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	//cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	scene_environment_with_multiple_lights environment; // The specific scene environment with multiple lights (*)
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                       // Standard GUI element storage

	cgp::skybox_drawable skybox;

	cgp::mesh_drawable cylinder;

	cgp::hierarchy_mesh_drawable hours;
	cgp::hierarchy_mesh_drawable minutes;
	cgp::hierarchy_mesh_drawable seconds;

	cgp::mesh_drawable maze;

	// Timers used for the animation
	cgp::timer_basic timer;

	// Flight
	cgp::timer_basic flight_timer;//independent timer for flight
	float flight_speed = 0.0f;//modifiable flight speed

	// Implicit surfaces
	implicit_surface_structure implicit_surface; // Structures used for the implicit surface (*)
	field_function_structure field_function;     // A Parametric function used to generate the discrete field (*)

	cgp::hierarchy_mesh_drawable nexus_core;
	cgp::hierarchy_mesh_drawable nexus;

	cgp::mesh_drawable halo;
	cgp::mesh_drawable blue_beam;
	cgp::mesh_drawable gold_beam;

	//orthographic projection gui
	cgp::mesh_drawable cube;
	cgp::scene_environment_basic environment_ortho;

	// text drawables
	// bool display_too_far;
	cgp::mesh_drawable text;
	bool display_text;
	float time_text_appeared;
	int idx_text;
	std::array<GLuint, 7> text_textures;


	// ****************************** //
	// Functions
	// ****************************** //

	// Function to call in the animation loop in main (*)
	// This function replace the standard trackball behavior that must also be removed in the main (from mouse_move_callback)
	void update_camera(); 
	void mouse_click(); // To activate nexus
	void activate_nexus(float d, int i);

	void initialize();  // Standard initialization to be called before the animation loop
	// std::vector<std::pair<int, int> > neighboring_walls(int i, int j);
	// void initialize_maze(int nl = 55, int nw = 55);

	void display();     // The frame display to be called within the animation loop
	void display_lights();
	void display_gui(); // The display of the GUI, also called within the animation loop
	void display_core();
	void display_semiTransparent(); // Display function for semi-transparent shapes
};

