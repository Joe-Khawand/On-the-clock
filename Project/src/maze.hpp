#pragma once
#include "cgp/cgp.hpp"

// std::array<int, 55*55> maze;
// cgp::mesh_drawable square;

// returns list of adjacent squares in random order using Knuth's shuffling algorithm
std::vector<std::pair<int, int> > neighboring_walls(int i, int j);

// builds maze via DFS algorithm
cgp::mesh initialize_maze(int nl = 155, int nw = 155, float c = 10.0f, float h = 50.0f);