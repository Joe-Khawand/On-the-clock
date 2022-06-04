#include "initial_scene.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace cgp;

void initial_scene_structure::initialize_initial_scene()
{
    //scene initiale
	initial_scene_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/Room.obj"));
	initial_scene_drawable.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	initial_scene_drawable.transform.translation = vec3(0,0,-20);
	initial_scene_drawable.transform.scaling = 4.0;

	clock_drawable.initialize(cgp::mesh_load_file_obj("assets/Objects/Clock.obj"));
	clock_drawable.transform.scaling = 0.1;
	clock_drawable.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);
	clock_drawable.transform.translation = {-13,0,-20};
}

void initial_scene_structure::display_initial_scene()
{
    draw(initial_scene_drawable, environment);
    draw(clock_drawable, environment);
    if(click){
        t_init += dt_init;
        environment.fog_falloff+=0.001*dt_init;
    }
    if(t_init>2.4){
        init=false;
        t_init=0.0;
        environment.camera.center_of_rotation= vec3(80,0,20);
        environment.camera.manipulator_rotate_spherical_coordinates(-M_PI_4,0);
    }
}