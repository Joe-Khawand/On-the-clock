#include "basket_scene.hpp"

#define _USE_MATH_DEFINES
 
#include <cmath>

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
				activate_nexus(d, i);
		}
		}
	}
}

void scene_structure::initialize()
{
	// Initialisation de la scene de basket
	basket_scene=false;
	transition=false;
	// Initial placement of the camera
	environment.camera.center_of_rotation= vec3{22,-22,0};
	environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_4,M_PI_4/2.0);

	// Initialize the skybox
	// ***************************************** //
	bright_skybox.initialize("assets/bright_skybox_hd/");
}

void scene_structure::display()
{
	dt_init=timer_init.update();
    if(click){
    t_init += dt_init;
    if (environment.fog_falloff>0.0001)
    {
        environment.fog_falloff-=0.0007*dt_init;
    }
    else{
        click=false;
        t_init=0.0;
    }
    }
    if (basket_scene)
    {
        if(transition){
            if (environment.fog_falloff>0.0001)
            {
                environment.fog_falloff-=0.0007*dt_init;
            }
            else{
                transition=false;
                t_init=0.0;
            }
        }
        draw(bright_skybox,environment);
    }
    else{
        // Update the current time
        dt=timer.update();
        if(environment.colors_displayed==6){
        
            t_init += dt_init;
            environment.fog_falloff+=0.001*dt_init;
            if(t_init>2.4){
                basket_scene=true;
                transition=true;
                environment.camera.center_of_rotation= vec3{80,0,20};
                environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_4,0);
            }
        }
    }
}		

void scene_structure::display_gui()
{
	ImGui::Checkbox("Wireframe", &gui.display.wireframe);
	ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 10.0f);
	ImGui::SliderFloat("Flight time scale", &flight_timer.scale, 0.0f, 10.0f);
	display_gui_falloff(environment);
}