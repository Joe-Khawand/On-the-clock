#include "scene.hpp"
#define _USE_MATH_DEFINES
 
#include <cmath>
//#include "terrain.hpp"
#include "clock_city.hpp"

using namespace cgp;
//float terrain_length = 20;
//int N_terrain_samples = 300;

void scene_structure::initialize()
{	// Initialize the skybox (*)
	// ***************************************** //
	skybox.initialize("assets/dark_skybox/");
	//skybox.transform.rotation=rotation_transform::from_axis_angle({ 0,1,0 }, M_PI_2);
	//skybox.transform.rotation=rotation_transform::from_axis_angle({ -1,0,0 }, -M_PI_2);

	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::z;
    environment.camera.look_at({ 1.f,100.0f,1.0f }, { 0,0,0 });

	mesh building_mesh = mesh_load_file_obj("assets/Objects/Building.obj");
	building.initialize(building_mesh,"building_obj");
	building.transform.scaling=0.2;
	building.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_2.initialize(building_mesh,"building_obj_2");
	building_3.initialize(building_mesh,"building_obj_3");
	building_4.initialize(building_mesh,"building_obj_4");
	building_5.initialize(building_mesh,"building_obj_5");
	building_6.initialize(building_mesh,"building_obj_6");
	building_7.initialize(building_mesh,"building_obj_7");
	building_8.initialize(building_mesh,"building_obj_8");
	building_9.initialize(building_mesh,"building_obj_9");
	building_10.initialize(building_mesh,"building_obj_10");
	building_2.transform.scaling=0.2;
	building_2.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_3.transform.scaling=0.2;
	building_3.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_4.transform.scaling=0.2;
	building_4.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_5.transform.scaling=0.2;
	building_5.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_6.transform.scaling=0.2;
	building_6.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_7.transform.scaling=0.2;
	building_7.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_8.transform.scaling=0.2;
	building_8.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_9.transform.scaling=0.2;
	building_9.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	building_10.transform.scaling=0.2;
	building_10.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);

	mesh tower_mesh = mesh_load_file_obj("assets/Objects/TOWER.obj");
	tower.initialize(tower_mesh,"tower_obj");
	tower.transform.scaling=10.0;
	tower.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);

	mesh ghetto_mesh = mesh_load_file_obj("assets/Objects/ghetto_building.obj");
	ghetto.initialize(ghetto_mesh,"ghetto_obj");
	ghetto.transform.scaling=0.4;
	ghetto.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);

	mesh nuclear_mesh = mesh_load_file_obj("assets/Objects/Nuclear_Cooling_Tower.obj");
	nuclear.initialize(nuclear_mesh,"nuclear_obj");
	nuclear.transform.scaling=0.0023;
	//nuclear.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);


    mesh arrow_mesh = create_arrow_mesh(0.2);
    arrow.initialize(arrow_mesh, "Arrow");
	arrow.transform.scaling=10.0;
	

	mesh ring_mesh = create_ring(9.0);
	ring.initialize(ring_mesh,"ring_mesh");
	ring.transform.scaling=10.0;

	city.add(arrow);
	city.add(tower,"Arrow",{7,1,2});
	city.add(building,"Arrow",{1.2,3.5,2});
	city.add(building_2,"Arrow",{1.2,1.5,2});
	city.add(building_3,"Arrow",{1.2,-0.5,2});
	city.add(building_4,"Arrow",{3.2,3.5,2});
	city.add(building_5,"Arrow",{3.2,-3.5,2});
	city.add(building_6,"Arrow",{5.2,-3.5,2});
	city.add(building_7,"Arrow",{34,-2.5,2});
	city.add(building_8,"Arrow",{34,2.5,2});
	city.add(building_9,"Arrow",{24,-2.5,2});
	city.add(building_10,"Arrow",{29,2.5,2});

	city.add(ghetto,"Arrow",{15,2,2});
	city.add(nuclear,"Arrow",{60,0,2});
	//city["ghetto_obj"].transform.rotation=rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);	
}



void scene_structure::display()
{
	draw(skybox, environment); 
	// Update the current time
	timer.update();

	// Basic elements of the scene
	environment.light = environment.camera.position();
	if (gui.display_frame)
		draw(global_frame, environment);
	//draw(world,environment);
	//draw(building,environment);
	//arrow.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	//draw(arrow, environment);
	//arrow.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t/12.0);
	//draw(arrow, environment);

	//draw(nuclear,environment);
	draw(city,environment);
	city["Arrow"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	draw(ring,environment);	

	// This function must be called before the drawing in order to propagate the deformations through the hierarchy
	city.update_local_to_global_coordinates();

	if (gui.display_wireframe){
		draw_wireframe(arrow, environment);
		draw_wireframe(ring, environment);
	}
        
}
void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
	ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 10.0f);

}


