#include "main_scene.hpp"

#define _USE_MATH_DEFINES
 
#include <cmath>

#include "clock_city.hpp"
#include "nexus.hpp"
#include "boids.hpp"
#include "main.cpp"


using namespace cgp;

void main_scene_structure::activate_nexus(float d, int i)
{
	// TODO move this to scene.cpp
	// if (d > 300.0f) {
	// 	scene.time_text_appeared = scene.timer.t;
	// 	display_text = true;
	// 	text.texture = opengl_load_texture_image("assets/Text/too_far.png");
	// }
	// else {
		if (!main_environment.spotlight_bool[i]){
			if (i > 0 && main_environment.spotlight_bool[0]) {
				main_environment.spotlight_color[i] = main_environment.spotlight_colors[i-1];
				main_environment.spotlight_timer[i].start();
				main_environment.spotlight_bool[i] = true;
				main_environment.spotlight_timer[0].scale += 0.1f;
				timer.scale += 0.1f;
				main_environment.colors_displayed += 1;
				number.clear();
				if (main_environment.colors_displayed < 12) {
					number.initialize(number_mesh(12-main_environment.colors_displayed));
					number.transform.translation = { 0.75f,0.8f,0.0f };
					number.transform.scaling = 0.01;
					number.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);
					number.shader = ortho_shader;
				}
				if (main_environment.colors_displayed < 5) {
					if (main_environment.colors_displayed == 1)
						main_environment.red_activated = main_environment.spotlight_timer[0].t;
					if (main_environment.colors_displayed == 2)
						main_environment.blue_activated = main_environment.spotlight_timer[0].t;
					if (main_environment.colors_displayed == 3)
						main_environment.green_activated = main_environment.spotlight_timer[0].t;
					if (main_environment.colors_displayed == 4)
						main_environment.textures_activated = main_environment.spotlight_timer[0].t;
				}
			}
			if (i == 0) {
				main_environment.spotlight_color[0] = {1, 1, 1};
				main_environment.spotlight_timer[0].start();
				main_environment.spotlight_bool[0] = true;
				main_environment.spotlight_timer[0].scale += 0.3f;
				main_environment.fog_falloff = 0.0000080f;
				timer.scale += 0.3f;
			}
		}
	// }
}

void main_scene_structure::initialize_main_scene()
{
	// // Initilisation dans la premiere scene
	// init=true;
	// click=false;
	// t_init = 0.0;
	// // Initialisation de la scene de basket
	// basket_scene=false;
	// transition=false;

	// Initial placement of the camera
	// TODO do we need to move this so that it is done only when we begin displaying the scene?
	// TODO actually since it's an independent scene moving the camera in another won't affect it so no probs (but we have to adapt update_camera function to implement this)
	main_environment.camera.center_of_rotation= vec3{22,-22,0};
	main_environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_4,M_PI_4/2.0);

	// Multiple lights
	// ***************************************** //
	GLuint const shader_lights = opengl_load_shader("shaders/mesh_lights/vert.glsl", "shaders/mesh_lights/frag.glsl");
	mesh_drawable::default_shader = shader_lights;   // set this shader as the default one for all new shapes declared after this line
	for (int i=0; i < n_lights; i++) {
		main_environment.spotlight_color[i] = { 0,0,0 };
		main_environment.spotlight_timer[i].stop();
	}
	main_environment.spotlight_color[0] = {1, 0.9, 0.8};
	main_environment.spotlight_timer[0].scale = 0;

	main_environment.spotlight_colors[0] = {1,0,0.5};
	main_environment.spotlight_colors[1] = {1,0,0};
	main_environment.spotlight_colors[2] = {1,0.5,0};
	main_environment.spotlight_colors[3] = {1,1,0};
	main_environment.spotlight_colors[4] = {0.5,1,0};
	main_environment.spotlight_colors[5] = {0,1,0};
	main_environment.spotlight_colors[6] = {0,1,0.5};
	main_environment.spotlight_colors[7] = {0,1,1};
	main_environment.spotlight_colors[8] = {0,0.5,1};
	main_environment.spotlight_colors[9] = {0,0,1};
	main_environment.spotlight_colors[10] = {0.5,0,1};
	main_environment.spotlight_colors[11] = {1,0,1};

	GLuint const shader_halo = opengl_load_shader("shaders/halos/vert.glsl", "shaders/halos/frag.glsl");

	// Initialize the skybox
	// ***************************************** //
	dark_skybox.initialize("assets/dark_skybox_hd/");

	// Initialize city
	// ***************************************** //
	timer.scale = 0.1f;
	hours = initialize_hours();
	minutes = initialize_minutes();
	seconds = initialize_seconds();

	central_cylinder.initialize(cgp::mesh_primitive_cylinder(0.6,{0,0,0},{0,0,3.0},2,20,true),"central cylinder");
	pulsating_cylinder_1.initialize(create_cylinder(2.0,1.5,0.5),"pulse1");
	pulsating_cylinder_2.initialize(create_cylinder(3.0,2.5,0.5),"pulse1");
	pulsating_cylinder_3.initialize(create_cylinder(2.0,1.5,0.5),"pulse1");
	central_cylinder.transform.translation={0,0,-25};
	pulsating_cylinder_1.transform.translation={0,0,-15.0};
	pulsating_cylinder_2.transform.translation={0,0,-12.0};
	pulsating_cylinder_3.transform.translation={0,0,-9.0};

	// Nexus beam and other semi-transparent billboards
	mesh quad_mesh_1 = mesh_primitive_quadrangle({ -30.0,0,-10 }, { 30.0,0,-10 }, { 30.0,0,10 }, { -30.0,0,10 });
	mesh quad_mesh_2 = mesh_primitive_quadrangle({ -5,-5,0 }, { 5,-5,0 }, { 5,5,0 }, { -5,5,0 });
	mesh quad_mesh_3 = mesh_primitive_quadrangle({ -5,0,-7 }, { 5.0,0,-7 }, { 5.0,0,40 }, { -5.0,0,40 });
	halo.initialize(quad_mesh_1, "Halo");
	gold_beam.initialize(quad_mesh_3,"Gold Beam");

	halo.texture = opengl_load_texture_image("assets/halo.png");
	gold_beam.texture = opengl_load_texture_image("assets/beamduloveforever.png");
	gold_beam.transform.scaling = 4;
	gold_beam.transform.translation = vec3(0, 0, -3);
	gold_beam.shader = shader_halo;
	halo.shader = shader_halo;

	// Implicit surface and nexuses
	// ***************************************** //

	// TODO check what this does
	// Helper to visualize the box of the domain
	segments_drawable::default_shader = curve_drawable::default_shader;

	// TODO check whether there is not conflict on redefinitions of default shaders left and right
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
	ortho_shader = opengl_load_shader("shaders/mesh/vert.glsl", "shaders/mesh/frag.glsl");
	number.shader = ortho_shader;

	mesh maze_mesh = initialize_maze(71, 71, 15, 50);
	maze.initialize(maze_mesh, "Maze");
	maze.transform.translation = {-525, -525, -200};

	//!Boids
	b = initialize_boids();
	//! Obj plane model oriente selon l'axe x, une reortentation est requise quand on alignera avec la vitesse
	boid_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/UFO_Triangle.obj"));
    boid_drawable.transform.scaling=0.0009;

	// //scene initiale
	// scene_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/Room.obj"));
	// scene_drawable.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// scene_drawable.transform.translation = vec3(0,0,-20);
	// scene_drawable.transform.scaling = 4.0;

	// clock_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/Clock.obj"));
	// clock_drawable.transform.scaling = 0.1;
	// clock_drawable.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);
	// clock_drawable.transform.translation = {-13,0,-20};
}


void main_scene_structure::display_main_scene()
{
	dt_init=timer_init.update();
	// if(init){
	// 	draw(scene_drawable,main_environment);
	// 	draw(clock_drawable, main_environment);
	// 	if(click){
	// 		t_init += dt_init;
	// 		main_environment.fog_falloff+=0.001*dt_init;
	// 	}
	// 	if(t_init>2.4){
	// 		init=false;
	// 		t_init=0.0;
	// 		main_environment.camera.center_of_rotation= vec3{80,0,20};
	// 		main_environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_4,0);
	// 	}
	// }
	// else{
		// if(click){
		// t_init += dt_init;
		// if (main_environment.fog_falloff>0.0001)
		// {
		// 	main_environment.fog_falloff-=0.0007*dt_init;
		// }
		// else{
		// 	click=false;
		// 	t_init=0.0;
		// }
		// }

	
		// if (basket_scene)
		// {
		// 	if(transition){
		// 		if (main_environment.fog_falloff>0.0001)
		// 		{
		// 			main_environment.fog_falloff-=0.0007*dt_init;
		// 		}
		// 		else{
		// 			transition=false;
		// 			t_init=0.0;
		// 		}
		// 	}
		// 	draw(bright_skybox,main_environment);
		// }
		// else{
			draw(dark_skybox, main_environment); 
			// Update the current time
			dt=timer.update();
			display_lights(); // displays each nexus and every light source
			if(main_environment.colors_displayed==6){
				t_init += dt_init;
				main_environment.fog_falloff+=0.001*dt_init;
				if(t_init>2.4){
					basket_scene=true;
					transition=true;
					main_environment.camera.center_of_rotation= vec3{80,0,20};
					main_environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_4,0);
				}
			}
			
			// Elements of the scene
		
			hours["Cylinder"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - timer.t / 36.0);
			hours.update_local_to_global_coordinates();
	
			draw(hours, main_environment);

			minutes["Cylinder"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - timer.t / 12.0);
			minutes.update_local_to_global_coordinates();

			draw(minutes, main_environment);

			seconds["Cylinder"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - angle_increment(timer.t));
			seconds.update_local_to_global_coordinates();

			draw(seconds, main_environment);
			
			central_cylinder.transform.translation={0,0,-25+15*sin(timer.t)};
			pulsating_cylinder_1.transform.translation={0,0,-15-sin(timer.t+10)};
			pulsating_cylinder_2.transform.translation={0,0,-12+sin(timer.t+2)};
			pulsating_cylinder_3.transform.translation={0,0,-9+sin(timer.t+10)};

			draw(central_cylinder,main_environment);
			draw(pulsating_cylinder_1,main_environment);
			draw(pulsating_cylinder_2,main_environment);
			draw(pulsating_cylinder_3,main_environment);

			pulsating_cylinder_1.transform.translation={0,0,-37-sin(timer.t+10)};
			pulsating_cylinder_2.transform.translation={0,0,-34+sin(timer.t+2)};
			pulsating_cylinder_3.transform.translation={0,0,-31+sin(timer.t+10)};

			draw(pulsating_cylinder_1,main_environment);
			draw(pulsating_cylinder_2,main_environment);
			draw(pulsating_cylinder_3,main_environment);
			draw(number, environment_ortho);
			
			draw(maze, main_environment);

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
				draw(boid_drawable,main_environment);
				if (gui.display.wireframe){
					draw_wireframe(boid_drawable,main_environment);
				}
			}
			
			if (gui.display.wireframe){
				draw_wireframe(hours, main_environment);
				draw_wireframe(minutes, main_environment);
				draw_wireframe(seconds, main_environment);
				draw_wireframe(gold_beam, main_environment);
				draw_wireframe(blue_beam, main_environment);
				draw_wireframe(maze, main_environment);
			}
			if (main_environment.spotlight_bool[0])
				display_semiTransparent();
		// }
	// }
}		

void main_scene_structure::display_lights()
{
	// Update the position and color of the lights
	compute_light_position(timer.t, main_environment);

	main_environment.spotlight_timer[0].update();
	float t0 = main_environment.spotlight_timer[0].t;
	nexus_core["Outer ring"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,1 }, 0.6743f * t0);
	nexus_core["Inner ring 1"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, M_PI * t0);
	nexus_core["Inner ring 2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.4142f * t0);
	nexus_core["Inner ring 3"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, - t0);

	nexus_core.update_local_to_global_coordinates();

	draw(nexus_core, main_environment);
	display_core();
	if (gui.display.wireframe)
	    draw_wireframe(nexus_core, main_environment);

	for(int i = 1; i<n_lights; i++){
		main_environment.spotlight_timer[i].update();
		float t = main_environment.spotlight_timer[i].t;
		nexus["Core"].transform.translation = main_environment.spotlight_position[i];
		float dilatation = (2.5 + 0.5 * pow(cos(2 * t), 10)) / 3.0f;
		nexus["Core"].transform.scaling = dilatation;
		nexus["Outer ring"].transform.scaling = 1 / dilatation;
		nexus["Outer ring"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,1 }, 0.6743f * t);
		nexus["Inner ring 1"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, M_PI * t);
		nexus["Inner ring 2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.4142f * t);
		nexus["Inner ring 3"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, - t);

		nexus.update_local_to_global_coordinates();
		draw(nexus, main_environment);
		if (gui.display.wireframe)
			draw_wireframe(nexus, main_environment);
	}

}

void main_scene_structure::display_core()
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
	
	draw(implicit_surface.drawable_param.shape, main_environment);

	if (gui.display.wireframe)  // Display the wireframe of the implicit surface (*)
		draw_wireframe(implicit_surface.drawable_param.shape, main_environment, { 0,0,0 });
}

void main_scene_structure::display_semiTransparent()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Disable depth buffer writing
	//  - Transparent elements cannot use depth buffer
	//  - They are supposed to be display from furest to nearest elements
	glDepthMask(false);

	// Draw the billboards two times
		gold_beam.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },0);
		draw(gold_beam,main_environment);
		gold_beam.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },M_PI_2);
		draw(gold_beam,main_environment);
		halo.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },0 );
		draw(halo, main_environment);
		halo.transform.rotation= rotation_transform::from_axis_angle({ 0,0,1 },M_PI_2 );
		draw(halo, main_environment);
		// if (display_text){
		// 	text.transform.translation = main_environment.camera.position() + 20 * main_environment.camera.front();
		// 	text.transform.rotation = main_environment.camera.orientation();
		// 	draw(text, main_environment);
		// 	if (timer.t - time_text_appeared > 1.0)
		// 		display_text = false;
		// }
	// Re-activate the depth-buffer write
	glDepthMask(true);
	glDisable(GL_BLEND);
}
