#include "scene.hpp"

#include "nexus.hpp"

using namespace cgp;

void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	// environment.camera.axis = camera_spherical_coordinates_axis::z;
    // environment.camera.look_at({ 1.f,10.0f,1.0f }, { 0,0,0 });

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

	// The ground
	ground.initialize(mesh_primitive_quadrangle({ -30,-30,-20 }, { -30,30,-20 }, { 30,30,-20 }, { 30,-30,-20 }), "Quad");

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
	// Basic elements of the scene
	//environment.light = vec3{0, 0, 0}; // environment.camera.position();
	timer.update();
	display_lights();
	display_core();
	display_nexus();
}


void scene_structure::display_gui()
{
	// ImGui::Checkbox("Frame", &gui.display.frame);
	// ImGui::Checkbox("Wireframe", &gui.display.wireframe);
	ImGui::SliderFloat("Nexus speed", &speed, 0.f, 4.0f);
	ImGui::SliderFloat("Speed of time", &speed_time, 0.f, 4.0f);
	display_gui_falloff(environment);
}


void scene_structure::display_lights()
{
	// Update the position and color of the lights
	compute_light_position(timer.t, environment);

	// Display the elements of the scene
	draw(ground, environment);
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
