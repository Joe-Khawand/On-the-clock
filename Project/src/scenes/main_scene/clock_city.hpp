#pragma once

#include "cgp/cgp.hpp"

// ****************************** //
// Functions
// ****************************** //

// Used locally

cgp::mesh create_arrow_mesh(float h, float l, float w);
cgp::mesh create_ring(float r);
cgp::mesh create_cylinder(float radius_1,float radius_2,float height, float uv_ratio = 15);
cgp::mesh brick(float l, float w, float h, cgp::vec3 offset = {0, 0, 0});
cgp::mesh v(float l, float w, float h, cgp::vec3 offset = {0, 0, 0});
cgp::mesh x(float l, float w, float h, cgp::vec3 offset = {0, 0, 0});
cgp::mesh create_city(float l, float w, float s, int nl, int nw, float hmax);
// TODO cgp::mesh maze(float nl, float nw, float h);


// Used externally

cgp::hierarchy_mesh_drawable initialize_hours();
cgp::hierarchy_mesh_drawable initialize_minutes();
cgp::hierarchy_mesh_drawable initialize_seconds();
cgp::mesh number_mesh(int nb);
float angle_increment(float t);
