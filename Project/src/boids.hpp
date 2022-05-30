#pragma once
#include <cmath>
#include "cgp/cgp.hpp"
#include <vector>

class Boid{
    public:
    cgp::vec3 position;
    cgp::vec3 vitesse;

    Boid();//constructeur 

    void draw_boid(float dt);
    float distance_to(Boid b);
};

const int number_boids=80;

//cube qui confine les boids
const float border_x=150.0;
const float border_y=150.0;
const float border_z=100.0;


// ****************************** //
// Functions
// ****************************** //

std::vector<Boid *> initialize_boids();

void separation(std::vector<Boid *> b);
void alignment(std::vector<Boid *> b);
void cohesion(std::vector<Boid *> b);


