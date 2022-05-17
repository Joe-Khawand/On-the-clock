#include "scene.hpp"

#define _USE_MATH_DEFINES
 
#include <cmath>

#include "clock_city.hpp"

#include "nexus.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Initialize the camera
	environment.projection = camera_projection::perspective(50.0f * Pi/180, 1.0f, 0.1f, 500.0f);
	environment.camera.distance_to_center = 30.0f;
	environment.camera.look_at({ 30,1,2 }, { 0,0,0 }, { 0,0,1 });


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
	//skybox.transform.rotation=rotation_transform::from_axis_angle({ 0,1,0 }, M_PI_2);
	//skybox.transform.rotation=rotation_transform::from_axis_angle({ -1,0,0 }, -M_PI_2);

	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");

	//environment.camera.axis = camera_spherical_coordinates_axis::z;
    //environment.camera.look_at({ 1.f,100.0f,1.0f }, { 0,0,0 });

	//Initialise city
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

	// mesh tower_mesh = mesh_load_file_obj("assets/Objects/TOWER.obj");
	// tower.initialize(tower_mesh,"tower_obj");
	// tower.transform.scaling=10.0;
	// tower.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);

	// mesh ghetto_mesh = mesh_load_file_obj("assets/Objects/ghetto_building.obj");
	// ghetto.initialize(ghetto_mesh,"ghetto_obj");
	// ghetto.transform.scaling=0.4;
	// ghetto.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);

	mesh nuclear_mesh = mesh_load_file_obj("assets/Objects/Nuclear_Cooling_Tower.obj");
	nuclear.initialize(nuclear_mesh,"nuclear_obj");
	nuclear.transform.scaling=0.0023;
	
    //mesh arrow_mesh = create_arrow_mesh(0.2);
	mesh arrow_mesh = create_arrow_mesh_bis(0.2, 7.0, 1.0);
    arrow.initialize(arrow_mesh, "Arrow");
	arrow.transform.scaling=10.0;
	

	mesh ring_mesh = create_ring(9.0);
	ring.initialize(ring_mesh,"ring_mesh");
	ring.transform.scaling=10.0;

	city.add(arrow);
	// city.add(tower,"Arrow",{7,1,2});
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

	// city.add(ghetto,"Arrow",{15,2,2});
	city.add(nuclear,"Arrow",{60,0,2});

	//city["Arrow"].global_transform.translation = vec3(17, 0, 0);
	//city["ghetto_obj"].transform.rotation=rotation_transform::from_axis_angle({ 0,0,1 }, M_PI_2);	

	//Nexus beam
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

	// The lights displayed as spheres using this helper initializer (*)-optionnal
	light_drawable.initialize(shader_lights);


	// Implicit surface and nexuses
	// ***************************************** //

	// Helper to visualize the box of the domain
	segments_drawable::default_shader = curve_drawable::default_shader;


	// Load the shader used to display the implicit surface (only a polygon soup)
	// GLuint shader_triangle_soup = opengl_load_shader("shaders/mesh_geometry/vert.glsl", "shaders/mesh_geometry/frag.glsl");
	GLuint shader_triangle_soup = opengl_load_shader("shaders/implicit_lights/vert.glsl", "shaders/implicit_lights/frag.glsl");
	triangle_soup_drawable::default_shader = shader_triangle_soup; //shader_lights; //

	// Initialize the field and the implicit surface
	implicit_surface.set_domain(gui.domain.samples, gui.domain.length);
	implicit_surface.update_field(field_function, gui.isovalue);

    //initialize_nexus();
	nexus_core = initialize_nexus(true);
	nexus = initialize_nexus(false);
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
	//environment.light = environment.camera.position();
	if (gui.display.frame)
		draw(global_frame, environment);
	//draw(world,environment);
	//draw(building,environment);
	//arrow.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	//draw(arrow, environment);
	//arrow.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t/12.0);
	//draw(arrow, environment);

	//draw(nuclear,environment);
	draw(city,environment);
	city["Arrow"].transform.translation = vec3(17 * cos(timer.t), 17 * sin(timer.t),0);
	city["Arrow"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	draw(ring,environment);	

	// This function must be called before the drawing in order to propagate the deformations through the hierarchy
	city.update_local_to_global_coordinates();

	if (gui.display.wireframe){
		draw_wireframe(arrow, environment);
		draw_wireframe(ring, environment);
	}
	display_semiTransparent();
        
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display.frame);
	ImGui::Checkbox("Wireframe", &gui.display.wireframe);
	ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 10.0f);
  	ImGui::SliderFloat("Nexus speed", &speed, 0.f, 4.0f);
	ImGui::SliderFloat("Speed of time", &speed_time, 0.f, 4.0f);
	display_gui_falloff(environment);
}

void scene_structure::display_lights()
{
	// Update the position and color of the lights
	compute_light_position(timer.t, environment);

	// Display the elements of the scene
	draw(light_drawable, environment); // this is a helper function from multiple_lights (display all the spotlights as spheres) (*)-optionnal
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


	// Re-orient the textures to always face the camera direction
	//vec3 const front = normalize(environment.camera.front() * vec3 { 1, 1, 0 }); // front-vector of the camera without z-component
	//vec3 const right = environment.camera.right();
	// Rotation such that R*{1,0,0} = right-direction, R*{0,1,0} = front-direction
	//rotation_transform R = rotation_transform::between_vector({ 1,0,0 }, { 0,1,0 }, right, front);
	//halo.transform.rotation = R;
	
		draw(gold_beam,environment);
		draw(halo, environment);
	
	// Don't forget to re-activate the depth-buffer write
	glDepthMask(true);
	glDisable(GL_BLEND);
}
