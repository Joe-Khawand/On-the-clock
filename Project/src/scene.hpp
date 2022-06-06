#pragma once

#include "cgp/cgp.hpp"
#include "implicit_surface/implicit_surface.hpp"
#include "implicit_surface/field_function.hpp"
#include "gui_helper.hpp"
#include "multiple_lights/multiple_lights.hpp" 
#include "clock_city.hpp"
#include "maze.hpp"
#include "boids.hpp"

// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //
	
	//scene bools

	bool init;
	bool clock;
	bool basket_scene;
	bool transition;
	bool click;
	bool click_basket;

	//elements de la premiere scene
	
	float t_init;
	float dt_init;
	
	cgp::timer_basic timer_init;
	cgp::mesh_drawable scene_drawable;
	cgp::mesh_drawable clock_drawable;

	//elements scene basket
	bool has_penetrated;
	float alpha;
	const cgp::vec3 g= { 0.0f,0.0f,-9.81f };;
	cgp::vec3 vit;
	cgp::vec3 pos;
	cgp::mesh_drawable terrain_drawable;
	cgp::skybox_drawable bright_skybox;
	float ball_radius = 4.0;
	cgp::mesh_drawable ball_drawable;

	// Drawable structure to display the particles and the spring
	cgp::mesh_drawable particle_sphere;
	cgp::segments_drawable segment;
	cgp::mesh_drawable hoop_structure;
	cgp::mesh_drawable board;

	int N_particles; // number of particles
    std::vector<cgp::vec3> particles_p; // position of all moving particles
    std::vector<cgp::vec3> particles_v; // velocity of all moving particles
    float L0; // Rest-length of spring

	
	//cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	scene_environment_with_multiple_lights environment; // The specific scene environment with multiple lights (*)
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                       // Standard GUI element storage

	cgp::skybox_drawable dark_skybox;
	

	cgp::mesh_drawable cylinder;
	cgp::mesh_drawable central_cylinder;
	cgp::mesh_drawable pulsating_cylinder_1;
	cgp::mesh_drawable pulsating_cylinder_2;
	cgp::mesh_drawable pulsating_cylinder_3;

	cgp::hierarchy_mesh_drawable hours;
	cgp::hierarchy_mesh_drawable minutes;
	cgp::hierarchy_mesh_drawable seconds;

	cgp::mesh_drawable maze;

	// Timers used for the animation
	cgp::timer_basic timer;
	float dt;

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
	cgp::mesh_drawable number;
	cgp::scene_environment_basic environment_ortho;
	GLuint ortho_shader;

	//! Boids
	std::vector<Boid *> b; //tableau de pointeurs vers des boids
	cgp::mesh_drawable boid_drawable;

	// text drawables
	// bool display_too_far;
	cgp::mesh_drawable text;
	bool display_text = false;
	float time_text_appeared = 0;
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

	void draw_scene_init();
	void draw_scene_clock();
	void draw_scene_basket();
	void draw_segment(cgp::vec3 const& a, cgp::vec3 const& b);
	cgp::vec3 spring_force(cgp::vec3 const& p_i, cgp::vec3 const& p_j, float L0, float K);
	void simulation_step(float dt);
	void initialize_net();
	void display_net();

	void transition_in();
	void transition_out();

	void display();     // The frame display to be called within the animation loop
	void display_lights();
	void display_gui(); // The display of the GUI, also called within the animation loop
	void display_core();
	void display_semiTransparent(); // Display function for semi-transparent shapes
	void display_text_billboard(float duration = 2.5f);
};

