#pragma once
#include <cmath>
#include "cgp/cgp.hpp"
#include <vector>

class Boid{
    public:
    cgp::vec3 position;
    cgp::vec3 vitesse;
    cgp::mesh_drawable shape;

    Boid();//constructor 
    //~Boid();//destructor

    void draw_boid(cgp::timer_basic time);
    float distance_to(Boid b);
    void apply_force();//apply force to boid changing its speed
    void steer(cgp::vec3 s);
};

//class Boids{
    //public:
    //const std::vector<Boid *> boids;
    const int number_boids=30;

    //cube confining the boids
    const float border_x=150.0;
    const float border_y=150.0;
    const float border_z=100.0;

    //cgp::timer_basic boid_timer;

    //Boids(int n);//constructor 
    std::vector<Boid *> initialize_boids();
//};


// ****************************** //
// Functions
// ****************************** //

void separation(std::vector<Boid *> b);
void alignment(std::vector<Boid *> b);
void cohesion(std::vector<Boid *> b);


