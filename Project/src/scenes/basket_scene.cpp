#include "basket_scene.hpp"

#define _USE_MATH_DEFINES
 
#include <cmath>

using namespace cgp;

void basket_scene_structure::initialize_basket_scene()
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

void basket_scene_structure::display_basket_scene()
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
