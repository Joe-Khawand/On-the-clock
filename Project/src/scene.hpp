#pragma once

#include "cgp/cgp.hpp"


// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame      = true;
	bool display_wireframe  = false;
};



// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	cgp::mesh_drawable global_frame;          // The standard global frame
	cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)

	gui_parameters gui;                       // Standard GUI element storage
	
	cgp::mesh_drawable arrow;
	cgp::mesh_drawable ring;
	cgp::mesh_drawable world;
	cgp::mesh_drawable tower;
	cgp::mesh_drawable ghetto;
	cgp::mesh_drawable nuclear;

	cgp::mesh_drawable building;
	cgp::mesh_drawable building_2;
	cgp::mesh_drawable building_3;
	cgp::mesh_drawable building_4;
	cgp::mesh_drawable building_5;
	cgp::mesh_drawable building_6;
	cgp::mesh_drawable building_7;
	cgp::mesh_drawable building_8;
	cgp::mesh_drawable building_9;
	cgp::mesh_drawable building_10;
	cgp::mesh_drawable building_11;


	cgp::skybox_drawable skybox;

	// Timer used for the animation
	cgp::timer_basic timer;


	cgp::hierarchy_mesh_drawable city;


	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop


};





