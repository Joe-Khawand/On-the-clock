#pragma once

#include "cgp/cgp.hpp"

struct perlin_noise_parameters
{
    float persistency = 0.55f;
    float frequency_gain = 2.4f;
    int octave = 9;
    float terrain_height = 1.f;
};

float evaluate_terrain_height(float x, float y);

/** Compute a terrain mesh 
	The (x,y) coordinates of the terrain are set in [-length/2, length/2].
	The z coordinates of the vertices are computed using evaluate_terrain_height(x,y).
	The vertices are sampled along a regular grid structure in (x,y) directions. 
	The total number of vertices is N*N (N along each direction x/y) 	*/
cgp::mesh create_terrain_mesh(int N, float length);
std::vector<cgp::vec3> generate_positions_on_terrain(int N, float terrain_length);
std::vector<cgp::vec3> generate_positions_mushrooms(int N, float terrain_length, std::vector<cgp::vec3> pi);
void update_terrain(cgp::mesh& terrain, cgp::mesh_drawable& terrain_visual, perlin_noise_parameters const& parameters, float terrain_length);
