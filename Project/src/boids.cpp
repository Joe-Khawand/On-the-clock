#include "boids.hpp"
//#include "scene.hpp"
#include <random>
#include <cmath>
#include <iostream>

//Boid constructor

Boid::Boid(){
    
    shape.initialize(cgp::mesh_primitive_cone(2.0,3.0,cgp::vec3{0,0,20})); 

    position= cgp::vec3{cgp::rand_interval(0,10.0),cgp::rand_interval(0,10.0),cgp::rand_interval(0,10.0)};
    vitesse= cgp::vec3{cgp::rand_interval(0,10.0),cgp::rand_interval(0,10.0),cgp::rand_interval(0,10.0)};
    //TODO normaliser la vitesse 
    //position+=vitesse*boid_timer.t;
}

float Boid::distance_to(Boid b){
    //TODO implement distance
    return sqrt(pow(position.x-b.position.x,2)+pow(position.y-b.position.y,2)+pow(position.z-b.position.z,2));
}

//TODO fix drawing
void Boid::draw_boid(cgp::timer_basic time){
    position= position + vitesse*time.t*0.01;
    if (position.x>= border_x)
    {
        vitesse.x = -abs(vitesse.x);
    }
    if(position.x<=-border_x){
        vitesse.x = abs(vitesse.x);
    }
    if (position.y>= border_y)
    {
        vitesse.y = -abs(vitesse.y);
    }
    if(position.y<=-border_y){
        vitesse.y = abs(vitesse.y);
    }
    if (position.z>= border_z)
    {
        vitesse.z = -abs(vitesse.z);
    }
    if(position.z<=-border_z){
        vitesse.z = abs(vitesse.z);
    }

    //vitesse= vitesse - position*time.t*0.001;
    cgp::vec3 norm_v = vitesse/ sqrt(vitesse.x*vitesse.x+vitesse.y*vitesse.y+vitesse.z*vitesse.z);
    shape.transform.rotation=cgp::rotation_transform::between_vector({0,0,1}, norm_v);
    shape.transform.translation= position;
    //!cgp::draw(shape,scene_structure::environment);
}

void Boid::steer(cgp::vec3 s){
    //cgp::vec3 norm_v = vitesse/ sqrt(vitesse.x*vitesse.x+vitesse.y*vitesse.y+vitesse.z*vitesse.z);
    //cgp::vec3 norm_s=  s/sqrt(s.x*s.x+s.y*s.y+s.z*s.z);
    vitesse = s;;
}

// Boids::Boids(int n){
//     number_boids = n;
//     boids.resize(n);
//     for (int i = 0; i < n; i++)
//     {
//        (boids[i]) = new Boid();
//     }
// }
std::vector<Boid *> initialize_boids(){
    std::vector<Boid *> boids;
    //number_boids=n;
    boids.resize(number_boids);
    for (int i = 0; i < number_boids; i++)
    {
       (boids[i]) = new Boid();
    }
    return boids;
}

// evite les collisions entre boids et entre la face du cube
void separation(std::vector<Boid *> boids){
    for (int i = 0; i < number_boids; i++)
    {   
        
        for (int j = 0; j < number_boids; j++)
        {
            if (j!=i)
            {
                if ((boids[i]->distance_to(*(boids[j])))<1.0)
                {//TODO steer
                    boids[i]->steer(cgp::vec3{0,0,1});
                }
                
            }
            
        }
        
    }
    
}
// Alignment
// Calculates the average velocity of boids in the field of vision and
// manipulates the velocity of the current boid in order to match it
//void alignment(std::vector<Boid *> b){};
// Cohesion
// Finds the average location of nearby boids and manipulates the
// steering force to move in that direction.
//void cohesion(std::vector<Boid *> b);