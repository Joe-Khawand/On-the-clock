#pragma once

#include "cgp/cgp.hpp"
#include "implicit_surface/implicit_surface.hpp"
#include "implicit_surface/field_function.hpp"
#include "gui_helper.hpp"
#include "multiple_lights/multiple_lights.hpp" 
#include "clock_city.hpp"
#include "boids.hpp"



// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	//cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	scene_environment_with_multiple_lights environment; // The specific scene environment with multiple lights (*)
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                       // Standard GUI element storage


	cgp::mesh_drawable halo;
	cgp::mesh_drawable blue_beam;
	cgp::mesh_drawable gold_beam;

	cgp::mesh_drawable cylinder;

	cgp::skybox_drawable skybox;

	// Timer used for the animation
	cgp::timer_basic timer;

	// Flight
	cgp::timer_basic flight_timer;//independent timer for flight
	float flight_speed= 0.0f;//modifiable flight speed

	// Implicit surfaces
	implicit_surface_structure implicit_surface; // Structures used for the implicit surface (*)
	field_function_structure field_function;     // A Parametric function used to generate the discrete field (*)

	// Speed of nexus
	float speed = 1.0f;
	float speed_time = 1.0f;

	//cgp::mesh_drawable nexus;
	cgp::hierarchy_mesh_drawable nexus_core;
	cgp::hierarchy_mesh_drawable nexus;

	//orthographic projection gui
	cgp::mesh_drawable cube;
	cgp::scene_environment_basic environment_ortho;
	cgp::hierarchy_mesh_drawable city;

	//! Boids
	//Boids boid_tab (int n);
	//cgp::timer_basic boid_timer;
	std::vector<Boid *> b;


	// ****************************** //
	// Functions
	// ****************************** //

	// Function to call in the animation loop in main (*)
	// This function replace the standard trackball behavior that must also be removed in the main (from mouse_move_callback)
	void update_camera(); 

	void initialize();  // Standard initialization to be called before the animation loop

	void display();     // The frame display to be called within the animation loop
	void display_lights();
	void display_gui(); // The display of the GUI, also called within the animation loop
	void display_core();
	void display_nexus();
	void display_semiTransparent(); // Display function for semi-transparent shapes
};

