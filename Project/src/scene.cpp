#include "scene.hpp"

#define _USE_MATH_DEFINES
 
#include <cmath>

using namespace cgp;

// The main function implementing the Flying Mode
// TODO add booleans allow_translation and allow_rotation
// TODO maybe we'll have to make another function if we create the maze scene to check collisions and stuff
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
	if(!init){
		
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
		if (keyboard.shift && !keyboard.ctrl)
			if (flight_speed<3.0)
			{
				flight_speed+=1.0f;
			}
			
		if (keyboard.ctrl && !keyboard.shift)
			if (flight_speed>-3.0)
			{
				flight_speed-=1.0f;
			}

		if (keyboard.shift && keyboard.ctrl)
				flight_speed=0.0f;
	}
}

// TODO adapt this so that it takes into account which scene is currently being displayed
void scene_structure::mouse_click()
{
	if (inputs.mouse.click.last_action == last_mouse_cursor_action::click_left) 
	{
		vec3 ray_direction = camera_ray_direction(environment.camera.matrix_frame(), environment.projection.matrix_inverse(), inputs.mouse.position.current);

		if (init)
		{
			vec3 cam_to_clock = cgp::vec3{-13,0,-7} - environment.camera.position();
			float s = cgp::norm(cam_to_clock);
			if (cgp::norm(s * normalize(ray_direction) - cam_to_clock) < 2.0f){
				//dt_init=timer_init.t;
				click= true;
			}
		}
		else{
			for (int i=0; i<n_lights; i++) {
			vec3 cam_to_light = environment.spotlight_position[i] - environment.camera.position();
			float d = cgp::norm(cam_to_light);
			if (cgp::norm(d * normalize(ray_direction) - cam_to_light) < 1.5f)
				main_environment.activate_nexus(d, i);
		}
		}
	}
}

void scene_structure::initialize()
{
	click=false;
	transition=false;
	text.texture = opengl_load_texture_image("assets/halo.png");
	
	// TODO
	initial_scene = true;
	initial_environment.initialize_initial_scene();

	main_scene = false;
	main_environment.initialize_main_scene();

	basket_scene = false;
	basket_environment.initialize_basket_scene();
}


void scene_structure::display()
{
	// TODO : update global timer used for transitions and displaying text
	dt_init=timer_init.update();

	if(click){
		t_init += dt_init; // TODO change so that it uses the global timer
		if (environment.fog_falloff>0.0001)
			environment.fog_falloff-=0.0007*dt_init;
		else{
			click=false;
			t_init=0.0;
		}
	}

	display_gui();
	// TODO : choose which scene to display and display it
	// // TODO : decide whether we keep the initial scene in the main scene or if we create a separate scene
	if (initial_scene)
		initial_environment.display_initial_scene();
	if (main_scene)
		main_environment.display_main_scene();
	if (basket_scene)
		basket_environment.display_basket_scene();

	if (display_text)
		display_text_billboard();
}		

void scene_structure::display_gui()
{
	ImGui::Checkbox("Wireframe", &gui.display.wireframe);
	ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 10.0f);
	ImGui::SliderFloat("Flight time scale", &flight_timer.scale, 0.0f, 10.0f);
	display_gui_falloff(environment);
}
