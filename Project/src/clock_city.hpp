#pragma once

#include "cgp/cgp.hpp"


cgp::mesh create_arrow_mesh(float h);
cgp::mesh create_arrow_mesh_bis(float h, float l, float w);
cgp::mesh create_ring(float r);
cgp::mesh create_cylinder(float radius_1,float radius_2,float height); // radius_1 > radius_2


