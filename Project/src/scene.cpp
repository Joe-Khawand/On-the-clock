#include "scene.hpp"

//#include "terrain.hpp"
//#include "tree.hpp"

using namespace cgp;
//float terrain_length = 20;
//int N_terrain_samples = 300;

void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::z;
    environment.camera.look_at({ 1.f,100.0f,1.0f }, { 0,0,0 });

//    terrain_mesh = create_terrain_mesh(N_terrain_samples, terrain_length);
//	terrain.initialize(terrain_mesh, "terrain");
//    update_terrain(terrain_mesh, terrain, parameters, terrain_length);
//    terrain.shading.color = { 0.6f,0.85f,0.5f };
//    //terrain.shading.color = {0.f, 1.f, 0.f};
//    GLuint const grass_texture_image_id = opengl_load_texture_image("assets/texture_grass.jpg",
//        GL_REPEAT,
//        GL_REPEAT);
//    terrain.texture = grass_texture_image_id;
//	terrain.shading.phong.specular = 0.0f; // non-specular terrain material

//    tree_position = generate_positions_on_terrain(200, terrain_length);
//    shroom_position = generate_positions_mushrooms(500, terrain_length, tree_position);

//    mesh tree_mesh = create_tree();
//    tree.initialize(tree_mesh, "tree");

//    mesh tree_trunk_mesh = create_tree_trunk();
//    tree_trunk.initialize(tree_trunk_mesh, "tree_trunk");
//    GLuint const trunk_texture_image_id = opengl_load_texture_image("assets/bark.jpg",
//        GL_REPEAT,
//        GL_REPEAT);
//    tree_trunk.texture = trunk_texture_image_id;

//    mesh tree_foliage_mesh = create_tree_foliage();
//    tree_foliage.initialize(tree_mesh, "tree_foliage");
//    GLuint const foliage_texture_image_id = opengl_load_texture_image("assets/needles.jpg",
//        GL_REPEAT,
//        GL_REPEAT);
//    tree_foliage.texture = foliage_texture_image_id;

//    mesh shroom_mesh = create_shroom();
//    shroom.initialize(shroom_mesh, "shroom");

//    mesh shroom_stump_mesh = create_shroom_stump();
//    shroom_stump.initialize(shroom_stump_mesh, "shroom_stump");

//    mesh shroom_cap_mesh = create_shroom_cap();
//    shroom_cap.initialize(shroom_cap_mesh, "shroom_cap");
//    GLuint const cap_texture_image_id = opengl_load_texture_image("assets/shroom.jpg",
//        GL_REPEAT,
//        GL_REPEAT);
//    shroom_cap.texture = cap_texture_image_id;


    // Init

//    //Initialize the temporary mesh_drawable that will be inserted in the hierarchy
//    mesh_drawable body;
//    mesh_drawable head;
//    mesh_drawable right_eye;
//    mesh_drawable left_eye;
//    mesh_drawable beak;
//    mesh_drawable right_wing_base;
//    mesh_drawable right_wing_tip;
//    mesh_drawable left_wing_base;
//    mesh_drawable left_wing_tip;


//    // Create the geometry of the meshes
//    //   Note: this geometry must be set in their local coordinates with respect to their position in the hierarchy (and with respect to their animation)
//    body.initialize(mesh_primitive_ellipsoid(vec3{0.4f, 0.26f, 0.18f}), "Body");
//    head.initialize(mesh_primitive_sphere(0.15f), "Head");
//    right_eye.initialize(mesh_primitive_sphere(0.03f), "Right eye");
//    left_eye.initialize(mesh_primitive_sphere(0.03f), "Left eye");
//    beak.initialize(mesh_primitive_cone(0.06f, 0.12f), "Beak");
//    right_wing_base.initialize(mesh_primitive_quadrangle({-0.2f,0,0}, {0.3f,0,0}, {0.3f,0.3f,0}, {-0.2f,0.3f,0}), "Right base");
//    right_wing_tip.initialize(mesh_primitive_quadrangle({-0.2f,0,0}, {0.3f,0,0}, {0.2f,0.3f,0}, {-0.1f,0.3f,0}), "Right tip");
//    left_wing_base.initialize(mesh_primitive_quadrangle({-0.2f,0,0}, {0.3f,0,0}, {0.3f,-0.3f,0}, {-0.2f,-0.3f,0}), "Left base");
//    left_wing_tip.initialize(mesh_primitive_quadrangle({-0.2f,0,0}, {0.3f,0,0}, {0.2f,-0.3f,0}, {-0.1f,-0.3f,0}), "Left tip");


//    // Set the color of some elements
//    vec3 black = { 0, 0, 0 };
//    right_eye.shading.color = black;
//    left_eye.shading.color = black;
//    vec3 orange = { 0.8f, 0.6f, 0.1f };
//    beak.shading.color = orange;

//     Add the elements in the hierarchy
//       The syntax is hierarchy.add(mesh_drawable, "name of the parent element", [optional: local translation in the hierarchy])
//       Notes:
//         - An element must necessarily be added after its parent
//         - The first element (without explicit name of its parent) is assumed to be the root.
//    bird.add(body);
//    bird.add(head, "Body");
//    bird.add(right_eye, "Head", { 0.12f,0.05f,0.06f }); // the translation is used to place the sphere at the extremity of the cylinder
//    bird.add(left_eye, "Head", { 0.12f,-0.05f,0.06f });
//    bird.add(beak, "Head", { 0.13f,0,0 }); // the translation is used to place the cube at the extremity of the cylinder
//    bird.add(right_wing_base, "Body", {0, 0.12f, 0});
//    bird.add(right_wing_tip, "Right base", {0, 0.3f, 0});
//    bird.add(left_wing_base, "Body", {0, -0.12f, 0});
//    bird.add(left_wing_tip, "Left base", {0, -0.3f, 0});
}



void scene_structure::display()
{

	// Basic elements of the scene
	environment.light = environment.camera.position();
	if (gui.display_frame)
		draw(global_frame, environment);

//    draw(terrain, environment);
//    if (gui.display_wireframe)
//        draw_wireframe(terrain, environment);

//    for(vec3 p : tree_position){
//        float x = p.x;
//        float y = p.y;
//        int ku = (x / terrain_length + 0.5f) * (N_terrain_samples - 1.0f);
//        int kv = (y / terrain_length + 0.5f) * (N_terrain_samples - 1.0f);
//        int const idx = ku * N_terrain_samples + kv;
//        float z = terrain_mesh.position[idx].z;
//        tree_trunk.transform.translation = vec3{x, y, z - 0.1f};
//        tree_foliage.transform.translation = vec3{x, y, z - 0.1f};
//        draw(tree_trunk, environment);
//        draw(tree_foliage, environment);
//        if (gui.display_wireframe){
//            draw_wireframe(tree_trunk, environment);
//            draw_wireframe(tree_foliage, environment);
//        }
//    }

//    for(vec3 s : shroom_position){
//        float x = s.x;
//        float y = s.y;
//        int ku = (x / terrain_length + 0.5f) * (N_terrain_samples - 1.0f);
//        int kv = (y / terrain_length + 0.5f) * (N_terrain_samples - 1.0f);
//        int const idx = ku * N_terrain_samples + kv;
//        float z = terrain_mesh.position[idx].z;
//        shroom_cap.transform.translation = vec3{x, y, z};
//        shroom_stump.transform.translation = vec3{x, y, z};
//        draw(shroom_cap, environment);
//        draw(shroom_stump, environment);
//        if (gui.display_wireframe){
//            draw_wireframe(shroom_cap, environment);
//            draw_wireframe(shroom_stump, environment);
//        }
//    }
}



void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);

//    bool update = false;
//    update |= ImGui::SliderFloat("Persistance", &parameters.persistency, 0.1f, 0.6f);
//    update |= ImGui::SliderFloat("Frequency gain", &parameters.frequency_gain, 1.5f, 2.5f);
//    update |= ImGui::SliderInt("Octave", &parameters.octave, 1, 10);
//    update |= ImGui::SliderFloat("Height", &parameters.terrain_height, 0.f, 1.5f);

//    if (update)// if any slider has been changed - then update the terrain
//        update_terrain(terrain_mesh, terrain, parameters, terrain_length);
}


