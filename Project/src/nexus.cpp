#include "nexus.hpp"
#include "cmath"

using namespace cgp;

mesh create_nexus_ring(float radius)
{
    float minor = 0.01 * radius;
    mesh outer_ring = mesh_primitive_torus(radius, minor, vec3{0, 0, 0}, vec3{0, 0, 1}, 100, 10);
    return outer_ring;
}

cgp::hierarchy_mesh_drawable initialize_nexus(bool is_core)
{
	float radius;
    float minor;
    if (is_core) {
        radius = 10.f;
        minor = 0.01 * radius;
    }
    else {
        radius = 1.5f;
        minor = 0.04 * radius;
    }

    hierarchy_mesh_drawable nexus;
	mesh core_mesh;
	mesh_drawable core;
	mesh_drawable outer_ring;
	mesh_drawable inner_ring1;
	mesh_drawable inner_ring2;
	mesh_drawable inner_ring3;

    if (is_core)
		core_mesh = mesh_primitive_sphere(0.001f, vec3{0, 0, 0});
	else
		core_mesh = mesh_primitive_sphere(0.5f, vec3{0, 0, 0});
	core_mesh.flip_connectivity();
	core.initialize(core_mesh, "Core");

	mesh ring0 = mesh_primitive_torus(radius, minor, vec3{0, 0, 0}, vec3{0, 0, 1}, 100, 10);
	outer_ring.initialize(ring0, "Outer ring");

	mesh ring1 = mesh_primitive_torus(radius - 2.5f * minor, minor, vec3{0, 0, 0}, vec3{0, 0, 1}, 100, 10);
	mesh cylinder = mesh_primitive_cylinder(0.9 * minor, vec3{0, 0, 0}, vec3{0, 2.5f * minor, 0});
	cylinder.position += vec3{0, radius - 2.5f * minor, 0};
	ring1.push_back(cylinder);
	cylinder.position -= vec3{0, radius - 2.5f * minor, 0};
	cylinder.position += vec3{0, - radius, 0};
	ring1.push_back(cylinder);
	cylinder.position -= vec3{0, - radius, 0};
	inner_ring1.initialize(ring1, "Inner ring 1");

	mesh ring2 = mesh_primitive_torus(radius - 5.f * minor, minor, vec3{0, 0, 0}, vec3{0, 0, 1}, 100, 10);
	cylinder = mesh_primitive_cylinder(0.9 * minor, vec3{0, 0, 0}, vec3{2.5f * minor, 0, 0});
	cylinder.position += vec3{radius - 5.f * minor, 0, 0};
	ring2.push_back(cylinder);
	cylinder.position -= vec3{radius - 5.f * minor, 0, 0};
	cylinder.position += vec3{- radius + 2.5f * minor, 0, 0};
	ring2.push_back(cylinder);
	cylinder.position -= vec3{- radius + 2.5f * minor, 0, 0};
	inner_ring2.initialize(ring2, "Inner ring 2");

	mesh ring3 = mesh_primitive_torus(radius - 7.5f * minor, minor, vec3{0, 0, 0}, vec3{0, 0, 1}, 100, 10);
	cylinder = mesh_primitive_cylinder(0.9 * minor, vec3{0, 0, 0}, vec3{0.7071f * 2.5f * minor, 0.7071f * 2.5f * minor, 0});
	cylinder.position += vec3{0.7071f * (radius - 7.5f * minor), 0.7071f * (radius - 7.5f * minor), 0};
	ring3.push_back(cylinder);
	cylinder.position -= vec3{0.7071f * (radius - 7.5f * minor), 0.7071f * (radius - 7.5f * minor), 0};
	cylinder.position += vec3{0.7071f * (- radius + 5.f * minor), 0.7071f * (- radius + 5.f * minor), 0};
	ring3.push_back(cylinder);
	cylinder.position -= vec3{0.7071f * (- radius + 5.f * minor), 0.7071f * (- radius + 5.f * minor), 0};
	inner_ring3.initialize(ring3, "Inner ring 3");

	GLuint silver_texture_image_id = opengl_load_texture_image("assets/silver.jpg",
        GL_REPEAT,
        GL_REPEAT);
	GLuint star_texture_image_id = opengl_load_texture_image("assets/star3.jpg",
        GL_REPEAT,
        GL_REPEAT);
	
	outer_ring.texture = silver_texture_image_id;
    inner_ring1.texture = silver_texture_image_id;
	inner_ring2.texture = silver_texture_image_id;
	inner_ring3.texture = silver_texture_image_id;
	core.texture = star_texture_image_id;

	nexus.add(core);
	nexus.add(outer_ring, "Core");
	nexus.add(inner_ring1, "Outer ring");
	nexus.add(inner_ring2, "Inner ring 1");
	nexus.add(inner_ring3, "Inner ring 2");

    return nexus;
}