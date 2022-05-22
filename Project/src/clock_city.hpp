#pragma once

#include "cgp/cgp.hpp"

struct city_test {
    cgp::mesh_drawable arrow;
    cgp::mesh_drawable ring;
    cgp::mesh_drawable world;
    cgp::mesh_drawable tower;
    cgp::mesh_drawable ghetto;
    cgp::mesh_drawable nuclear;

    cgp::mesh_drawable building;
    cgp::mesh_drawable building_2;
    cgp::mesh_drawable building_3;
    cgp::mesh_drawable building_4;
    cgp::mesh_drawable building_5;
    cgp::mesh_drawable building_6;
    cgp::mesh_drawable building_7;
    cgp::mesh_drawable building_8;
    cgp::mesh_drawable building_9;
    // cgp::mesh_drawable building_10;
    cgp::mesh_drawable building_11;

    cgp::hierarchy_mesh_drawable city;
};

cgp::hierarchy_mesh_drawable initialize_city(city_test cityy);

// ****************************** //
// Functions
// ****************************** //

// cgp::mesh create_arrow_mesh(float h);
cgp::mesh create_arrow_mesh(float h, float l, float w);
cgp::mesh create_ring(float r);
cgp::mesh create_cylinder(float radius_1,float radius_2,float height); // radius_1 > radius_2
