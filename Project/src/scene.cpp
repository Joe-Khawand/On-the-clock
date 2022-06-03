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
	// The rotation is only applied to the yaw and pitch degrees of freedom.
	float const pitch = 0.5f; // speed of the pitch
	float const yaw  = 0.7f; // speed of the yaw
	float scale = std::max(flight_timer.scale, 0.01f);

	if (keyboard.up){
		environment.camera.manipulator_rotate_spherical_coordinates(0,pitch*dt / scale);
	}
	if (keyboard.down){
		environment.camera.manipulator_rotate_spherical_coordinates(0,-pitch*dt / scale);
	}
	if (keyboard.right){
		environment.camera.manipulator_rotate_spherical_coordinates(yaw*dt / scale,0);
	}
	if (keyboard.left){
		environment.camera.manipulator_rotate_spherical_coordinates(-yaw*dt / scale,0);
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

void scene_structure::mouse_click()
{
	if (inputs.mouse.click.last_action == last_mouse_cursor_action::click_left) 
	{
		vec3 ray_direction = camera_ray_direction(environment.camera.matrix_frame(), environment.projection.matrix_inverse(), inputs.mouse.position.current);

		if (init)
		{
			vec3 cam_to_clock = cgp::vec3{-13,0,13} - environment.camera.position();
			float s = cgp::norm(cam_to_clock);
			if (cgp::norm(s * normalize(ray_direction) - cam_to_clock) < 2.0f)
				init=false;
		}
		else{
			for (int i=0; i<n_lights; i++) {
			vec3 cam_to_light = environment.spotlight_position[i] - environment.camera.position();
			float d = cgp::norm(cam_to_light);
			if (cgp::norm(d * normalize(ray_direction) - cam_to_light) < 1.5f)
				activate_nexus(d, i);
		}
		}
	}
}

void scene_structure::activate_nexus(float d, int i)
{
	if (d > 300.0f) {
		time_text_appeared = timer.t;
		display_text = true;
		text.texture = text_textures[0];
	}
	else {
		if (!environment.spotlight_bool[i]){
			if (i > 0 && environment.spotlight_bool[0]) {
				environment.spotlight_color[i] = { 1.0f, 0.9f, 0.5f };
				environment.spotlight_timer[i].start();
				environment.spotlight_bool[i] = true;
				environment.spotlight_timer[0].scale += 0.1f;
				timer.scale += 0.1f;
				environment.colors_displayed += 1;
				number.clear();
				number.initialize(number_mesh(12-environment.colors_displayed));
				number.transform.translation = { 0.75f,0.8f,0.0f };
				number.transform.scaling = 0.01;
				number.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);
				number.shader = opengl_load_shader("shaders/mesh/vert.glsl", "shaders/mesh/frag.glsl");
				if (environment.colors_displayed < 4) {
					if (environment.colors_displayed == 1)
						environment.red_activated = environment.spotlight_timer[0].t;
					if (environment.colors_displayed == 2)
						environment.blue_activated = environment.spotlight_timer[0].t;
					if (environment.colors_displayed == 3)
						environment.green_activated = environment.spotlight_timer[0].t;
					if (environment.colors_displayed == 4)
						environment.textures_activated = environment.spotlight_timer[0].t;
				}
			}
			if (i == 0) {
				environment.spotlight_color[0] = {1, 1, 1}; //{ 1.0f, 0.9f, 0.5f };
				environment.spotlight_timer[0].start();
				environment.spotlight_bool[0] = true;
				environment.spotlight_timer[0].scale += 0.3f;
				timer.scale += 0.3f;
			}
		}
	}
}

void scene_structure::initialize()
{
	// Initilisation dans la premiere scene
	init=true;
	// Initial placement of the camera
	environment.camera.center_of_rotation= vec3{80,0,20};
	environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_2,0);

	// Multiple lights
	// ***************************************** //
	GLuint const shader_lights = opengl_load_shader("shaders/mesh_lights/vert.glsl", "shaders/mesh_lights/frag.glsl");
	mesh_drawable::default_shader = shader_lights;   // set this shader as the default one for all new shapes declared after this line
	for (int i=0; i < n_lights; i++) {
		environment.spotlight_color[i] = { 0,0,0 };
		environment.spotlight_timer[i].stop();
	}
	environment.spotlight_color[0] = {1, 0.9, 0.8};
	environment.spotlight_timer[0].scale = 0;

	GLuint const shader_halo = opengl_load_shader("shaders/halos/vert.glsl", "shaders/halos/frag.glsl");

	// Initialize the skybox (*)
	// ***************************************** //
	skybox.initialize("assets/dark_skybox_hd/");

	// Initialize city
	// ***************************************** //
	timer.scale = 0.1f;
	hours = initialize_hours();
	minutes = initialize_minutes();
	seconds = initialize_seconds();

	// Nexus beam and other semi-transparent billboards
	mesh quad_mesh_1 = mesh_primitive_quadrangle({ -30.0,0,-10 }, { 30.0,0,-10 }, { 30.0,0,10 }, { -30.0,0,10 });
	mesh quad_mesh_2 = mesh_primitive_quadrangle({ -5,-5,0 }, { 5,-5,0 }, { 5,5,0 }, { -5,5,0 });
	mesh quad_mesh_3 = mesh_primitive_quadrangle({ -5,0,-7 }, { 5.0,0,-7 }, { 5.0,0,40 }, { -5.0,0,40 });
	halo.initialize(quad_mesh_1, "Halo");
	gold_beam.initialize(quad_mesh_3,"Gold Beam");
	text.initialize(quad_mesh_2, "Too far");

	halo.texture = opengl_load_texture_image("assets/halo.png");
	gold_beam.texture = opengl_load_texture_image("assets/beamduloveforever.png");
	text_textures[0] = opengl_load_texture_image("assets/Text/too_far.png");
	gold_beam.transform.scaling = 4;
	gold_beam.transform.translation = vec3(0, 0, -3);
	gold_beam.shader = shader_halo;
	halo.shader = shader_halo;
	text.shader = shader_halo;

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
	environment_ortho.light = { -1,-1,-1 };
	environment_ortho.camera.look_at({ 0, 0, 0.5f }, {0,0,0}, {0,1,0});
	number.initialize(number_mesh(12), "Number");
	number.transform.translation = { 0.75f,0.8f,0.0f };
	number.transform.scaling = 0.01;
	number.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);
	number.shader = opengl_load_shader("shaders/mesh/vert.glsl", "shaders/mesh/frag.glsl");

	mesh maze_mesh = initialize_maze();
	maze.initialize(maze_mesh, "Maze");
	maze.transform.translation = {-525, -525, -200};

	//!Boids
	b = initialize_boids();
	//! Obj plane model oriente selon l'axe x, une reortentation est requise quand on alignera avec la vitesse
	boid_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/UFO_Triangle.obj"));
    boid_drawable.transform.scaling=0.0009;

	scene_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/Room.obj"));
	scene_drawable.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	scene_drawable.transform.translation = vec3(0,0,-20);
	spherre.initialize(mesh_primitive_sphere(1, vec3(0,0,0)).flip_connectivity());
	scene_drawable.transform.scaling = 4.0;

	clock_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/Clock.obj"));
	clock_drawable.transform.scaling = 0.1;
	clock_drawable.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);
	clock_drawable.transform.translation = {-13,0,0};
}


void scene_structure::display()
{
	if(init){
		draw(scene_drawable,environment);
		draw(spherre, environment);
	}
	else{
		draw(skybox, environment); 
		// Update the current time
		dt=timer.update();
		display_lights(); // displays each nexus and every light source

		// Basic elements of the scene
	
		hours["Cylinder"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - timer.t / 36.0);
		hours.update_local_to_global_coordinates();
		draw(hours, environment);

		minutes["Cylinder"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - timer.t / 12.0);
		minutes.update_local_to_global_coordinates();
		draw(minutes, environment);

		seconds["Cylinder"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - angle_increment(timer.t));
		seconds.update_local_to_global_coordinates();
		draw(seconds, environment);
		

		// Scene_orthographic has a fixed camera and an orthographic projection : Player GUI
		// number.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.1f * M_PI_2)
		//                         * rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
		// number.transform.translation = { 0.75f, 0.8f, 0.0f };
		// draw(number, environment_ortho);
		// number.transform.translation = { 0.65f, 0.8f, 0.0f };
		// draw(number, environment_ortho);
		// number.transform.translation = { 0.55f, 0.8f, 0.0f };
		// draw(number, environment_ortho);
		draw(number, environment_ortho);
		

		draw(maze, environment);


		//! Boids
		//* Appliquer les 3 regles
		separation(b);
		alignment(b);
		cohesion(b);
		//dessiner les boids
		for (int i = 0; i < number_boids; i++)
		{	
			b[i]->draw_boid(dt);
			boid_drawable.transform.translation= b[i]->position;
		
			if(cgp::norm(b[i]->vitesse)>0.000001){
				//! changed start vector from vec{0,0,1} to vec3{-1,0,0} when we switched to the obj plane model
				boid_drawable.transform.rotation=cgp::rotation_transform::between_vector(cgp::vec3{-1.0,0,0}, cgp::normalize(b[i]->vitesse));
			}
			draw(boid_drawable,environment);
			if (gui.display.wireframe){
				draw_wireframe(boid_drawable,environment);
			}
		}
		

		if (gui.display.wireframe){
			draw_wireframe(hours, environment);
			draw_wireframe(minutes, environment);
			draw_wireframe(seconds, environment);
			draw_wireframe(gold_beam, environment);
			draw_wireframe(blue_beam, environment);
			draw_wireframe(maze, environment);
		}
		if (environment.spotlight_bool[0])
			display_semiTransparent();
	}
}

void scene_structure::display_gui()
{
	ImGui::Checkbox("Wireframe", &gui.display.wireframe);
	ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 10.0f);
	ImGui::SliderFloat("Flight time scale", &flight_timer.scale, 0.0f, 10.0f);
	display_gui_falloff(environment);
}

void scene_structure::display_lights()
{
	// Update the position and color of the lights
	compute_light_position(timer.t, environment);

	environment.spotlight_timer[0].update();
	float t0 = environment.spotlight_timer[0].t;
	nexus_core["Outer ring"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,1 }, 0.6743f * t0);
	nexus_core["Inner ring 1"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, M_PI * t0);
	nexus_core["Inner ring 2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.4142f * t0);
	nexus_core["Inner ring 3"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, - t0);

	nexus_core.update_local_to_global_coordinates();

	draw(nexus_core, environment);
	display_core();
	if (gui.display.wireframe)
	    draw_wireframe(nexus_core, environment);

	for(int i = 1; i<n_lights; i++){
		environment.spotlight_timer[i].update();
		float t = environment.spotlight_timer[i].t;
		nexus["Core"].transform.translation = environment.spotlight_position[i];
		float dilatation = (2.5 + 0.5 * pow(cos(2 * t), 10)) / 3.0f;
		nexus["Core"].transform.scaling = dilatation;
		nexus["Outer ring"].transform.scaling = 1 / dilatation;
		nexus["Outer ring"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,1 }, 0.6743f * t);
		nexus["Inner ring 1"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, M_PI * t);
		nexus["Inner ring 2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.4142f * t);
		nexus["Inner ring 3"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, - t);

		nexus.update_local_to_global_coordinates();
		draw(nexus, environment);
		if (gui.display.wireframe)
			draw_wireframe(nexus, environment);
	}

}

void scene_structure::display_core()
{
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
	implicit_surface.update_field(field_function, gui.isovalue);
	
	draw(implicit_surface.drawable_param.shape, environment);

	if (gui.display.wireframe)  // Display the wireframe of the implicit surface (*)
		draw_wireframe(implicit_surface.drawable_param.shape, environment, { 0,0,0 });
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
		if (display_text){
			text.transform.translation = environment.camera.position() + 20 * environment.camera.front();
			text.transform.rotation = environment.camera.orientation();
			draw(text, environment);
			if (timer.t - time_text_appeared > 1.0)
				display_text = false;
		}
	// Re-activate the depth-buffer write
	glDepthMask(true);
	glDisable(GL_BLEND);
}
