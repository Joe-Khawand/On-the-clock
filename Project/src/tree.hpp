#pragma once

#include "cgp/cgp.hpp"


cgp::mesh create_arrow_mesh(float h);
cgp::mesh create_ring(float r);
cgp::mesh create_cone_mesh(float radius, float height, float z_offset);
cgp::mesh create_tree();
cgp::mesh create_tree_foliage();
cgp::mesh create_shroom();
cgp::mesh create_shroom_cap();
cgp::mesh create_shroom_stump();
