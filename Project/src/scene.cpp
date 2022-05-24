#include "scene.hpp"

#define _USE_MATH_DEFINES
 
#include <cmath>

#include "clock_city.hpp"

#include "nexus.hpp"

#include "boids.hpp"


using namespace cgp;

// The main function implementing the Flying Mode
void scene_structure::update_camera()
{
	inputs_keyboard_parameters const& keyboard = inputs.keyboard;

	// flight_speed modifiable avec shift et ctrl
	float const dt = flight_timer.update();
	vec3 const forward_displacement = flight_speed * 3.0f * dt * environment.camera.front();
	environment.camera.center_of_rotation+= forward_displacement;
	environment.camera.axis=camera_spherical_coordinates_axis::z;

	// The camera rotates if we press on the arrow keys
	//  The rotation is only applied to the yaw and pitch degrees of freedom.
	float const pitch = 0.5f; // speed of the pitch
	float const yaw  = 0.7f; // speed of the yaw

	if (keyboard.up){
		environment.camera.manipulator_rotate_spherical_coordinates(0,pitch*dt);
	}
	if (keyboard.down){
		environment.camera.manipulator_rotate_spherical_coordinates(0,-pitch*dt);
	}
	if (keyboard.right){
		environment.camera.manipulator_rotate_spherical_coordinates(yaw*dt,0);
	}
	if (keyboard.left){
		environment.camera.manipulator_rotate_spherical_coordinates(-yaw*dt,0);
	}
	if (keyboard.shift)
		if (flight_speed<3.0)
		{
			flight_speed+=1.0f;
		}
		
	if (keyboard.ctrl)
		if (flight_speed>-3.0)
		{
			flight_speed-=1.0f;
		}
}

void scene_structure::initialize()
{
	// Initial placement of the camera
	environment.camera.center_of_rotation= vec3{80,0,20};
	environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_2,0);

	// Multiple lights
	// ***************************************** //

	// Specific Shader (*)
	// Load a new custom shader that take into account spotlights (note the new shader file in shader/ directory)
	// Make sure you load an set this shader for the shapes that need to be illuminated
	GLuint const shader_lights = opengl_load_shader("shaders/mesh_lights/vert.glsl", "shaders/mesh_lights/frag.glsl");
	mesh_drawable::default_shader = shader_lights;   // set this shader as the default one for all new shapes declared after this line

	GLuint const shader_halo = opengl_load_shader("shaders/halos/vert.glsl", "shaders/halos/frag.glsl");


	// Initialize the skybox (*)
	// ***************************************** //
	skybox.initialize("assets/dark_skybox_hd/");

	// Initialize city
	// ***************************************** //
	city_struct city_temp;
	city = initialize_city(city_temp);	

	mesh cylinder_mesh= create_cylinder(100,90, 5);
	cylinder.initialize(cylinder_mesh,"Cylindre");

	// Nexus beam
	mesh quad_mesh_1 = mesh_primitive_quadrangle({ -30.0,0,-10 }, { 30.0,0,-10 }, { 30.0,0,10 }, { -30.0,0,10 });
	mesh quad_mesh_2 = mesh_primitive_quadrangle({ -5.0,0,-10 }, { 5.0,0,-10 }, { 5.0,0,10 }, { -5.0,0,10 });
	mesh quad_mesh_3 = mesh_primitive_quadrangle({ -5.0,0,-7 }, { 5.0,0,-7 }, { 5.0,0,40 }, { -5.0,0,40 });
	halo.initialize(quad_mesh_1, "Halo");
	gold_beam.initialize(quad_mesh_3,"Gold Beam");

	halo.texture = opengl_load_texture_image("assets/halo.png");
	gold_beam.texture = opengl_load_texture_image("assets/beamduloveforever.png");
	gold_beam.transform.scaling = 4;
	gold_beam.transform.translation = vec3(0, 0, -3);
	gold_beam.shader = shader_halo;
	halo.shader = shader_halo;

	halo.shading.phong = { 0.4f, 0.6f,0,1 };
	gold_beam.shading.phong = { 0.4f, 0.6f,0,1 };

	// Implicit surface and nexuses
	// ***************************************** //

	// Helper to visualize the box of the domain
	segments_drawable::default_shader = curve_drawable::default_shader;


	// Load the shader used to display the implicit surface (only a polygon soup)
	GLuint shader_triangle_soup = opengl_load_shader("shaders/implicit_lights/vert.glsl", "shaders/implicit_lights/frag.glsl");
	triangle_soup_drawable::default_shader = shader_triangle_soup; //shader_lights; //

	// Initialize the field and the implicit surface
	implicit_surface.set_domain(gui.domain.samples, gui.domain.length);
	implicit_surface.update_field(field_function, gui.isovalue);

    //initialize_nexus();
	nexus_core = initialize_nexus(true);
	nexus = initialize_nexus(false);

	// Set the second scene with the orthographic project
	//*****************************************************
	environment_ortho.projection = camera_projection::orthographic(-1, 1, -1, 1, -1, 1);
	environment_ortho.camera.distance_to_center = 2.5f;
	environment_ortho.light = { 0,0,1 };
	environment_ortho.camera.look_at({ 0, 0, 0.5f }, {0,0,0}, {0,1,0});
	cube.initialize(mesh_primitive_cube({ 0,0,0 }, 0.2f), "Cube");
	cube.transform.translation = { 0.75f,0.8f,0.0f };
	cube.transform.scaling = 0.2;

	//!Boids
	b = initialize_boids();
}


void scene_structure::display()
{

	draw(skybox, environment); 
	// Update the current time
	timer.update();
	display_lights();
	display_core();
	display_nexus();

	// Basic elements of the scene
  
	draw(city,environment);
	city["Arrow"].transform.translation = vec3(17 * cos(timer.t), 17 * sin(timer.t),0);
	city["Arrow"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	city.update_local_to_global_coordinates();

	draw(cylinder,environment);	

	// Scene_orthographic has a fixed camera and an orthographic projection : Player GUI
	cube.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.1f * M_PI_2)
                            * rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	cube.transform.translation = { 0.75f, 0.8f, 0.0f };
	draw(cube, environment_ortho);
	cube.transform.translation = { 0.65f, 0.8f, 0.0f };
	draw(cube, environment_ortho);
	cube.transform.translation = { 0.55f, 0.8f, 0.0f };
	draw(cube, environment_ortho);

	//! Boids
	//boid_timer.update();
	//separation(b);
	for (int i = 0; i < number_boids; i++)
	{	
		b[i]->draw_boid(timer);
		draw(b[i]->shape,environment);
	}
	

	// TODO (later on tho)
	if (gui.display.wireframe){
		draw_wireframe(cylinder,environment);
	}
	display_semiTransparent();
        
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display.frame);
	ImGui::Checkbox("Wireframe", &gui.display.wireframe);
	ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 10.0f);
	ImGui::SliderFloat("Flight time scale", &flight_timer.scale, 0.0f, 10.0f);
  	ImGui::SliderFloat("Nexus speed", &speed, 0.f, 4.0f);
	ImGui::SliderFloat("Speed of time", &speed_time, 0.f, 4.0f);
	display_gui_falloff(environment);
}

void scene_structure::display_lights()
{
	// Update the position and color of the lights
	compute_light_position(timer.t, environment);

	int const N_spotlight = environment.spotlight_color.size();
	for(u_int k_light = 1; k_light<N_spotlight; k_light++){
		nexus["Core"].transform.translation = environment.spotlight_position[k_light];
		nexus.update_local_to_global_coordinates();
		draw(nexus, environment);
	}

}


void scene_structure::display_core()
{
	if (gui.display.surface)    // Display the implicit surface (*)
	field_function.pa = {  2 * cos(3 * timer.t),
						sin(3 * timer.t),
						0.0f};
	field_function.pb = { 3 * cos(3 * timer.t) * cos(3 * timer.t + 17.f),
						1.7 * cos(3 * timer.t)* sin(3 * timer.t + 17.f),
						2.3 * sin(3 * timer.t) };
	field_function.pc = { 2.3 * cos(- 4 * timer.t),
						0.4 * sin(- 4 * timer.t) * sin(- 1.17 * timer.t),
						1.9 * sin(- 4 * timer.t) * cos(- 1.17 * timer.t) };
	field_function.noise_offset = 1000 * timer.t;
	implicit_surface.gui_update(gui, field_function);
	
	draw(implicit_surface.drawable_param.shape, environment);

	if (gui.display.wireframe)  // Display the wireframe of the implicit surface (*)
		draw_wireframe(implicit_surface.drawable_param.shape, environment, { 0,0,0 });
}

void scene_structure::display_nexus()
{
	nexus_core["Outer ring"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,1 }, 0.6743f * speed * timer.t);
	nexus_core["Inner ring 1"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, M_PI * speed * timer.t);
	nexus_core["Inner ring 2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.4142f * speed * timer.t);
	nexus_core["Inner ring 3"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, - speed * timer.t);

	nexus_core.update_local_to_global_coordinates();

	nexus["Core"].transform.scaling = (2.5 + 0.5 * pow(cos(2 * timer.t), 10)) / 3.0f;
	nexus["Outer ring"].transform.scaling = 1 / ((2.5 + 0.5 * pow(cos(2 * timer.t), 10)) / 3.0f);
	nexus["Outer ring"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,1 }, 0.6743f * speed * timer.t);
	nexus["Inner ring 1"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, M_PI * speed * timer.t);
	nexus["Inner ring 2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.4142f * speed * timer.t);
	nexus["Inner ring 3"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, - speed * timer.t);

	nexus["Core"].transform.translation = vec3{20, 0, 0};
	nexus.update_local_to_global_coordinates();
	//draw(nexus, environment);
	if (gui.display.wireframe)
		draw_wireframe(nexus, environment, { 0,0,0 });
	
	nexus["Core"].transform.translation = vec3{-20, 0, 0};
	nexus.update_local_to_global_coordinates();
	//draw(nexus, environment);
	if (gui.display.wireframe)
		draw_wireframe(nexus, environment, { 0,0,0 });

	nexus["Core"].transform.translation = vec3{15, 10, 0};
	nexus.update_local_to_global_coordinates();
	//draw(nexus, environment);
	if (gui.display.wireframe)
		draw_wireframe(nexus, environment, { 0,0,0 });

	draw(nexus_core, environment);
	if (gui.display.wireframe)
	    draw_wireframe(nexus_core, environment);
}

void scene_structure::display_semiTransparent()
{
	// Enable use of alpha component as color blending for transparent elements
	//  alpha = current_color.alpha
	//  new color = previous_color * alpha + current_color * (1-alpha)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Disable depth buffer writing
	//  - Transparent elements cannot use depth buffer
	//  - They are supposed to be display from furest to nearest elements
	glDepthMask(false);

	// Draw the billboards two times
		gold_beam.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },0);
		draw(gold_beam,environment);
		gold_beam.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },M_PI_2);
		draw(gold_beam,environment);
		halo.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },0 );
		draw(halo, environment);
		halo.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },M_PI_2 );
		draw(halo, environment);
	
	// Re-activate the depth-buffer write
	glDepthMask(true);
	glDisable(GL_BLEND);
}
