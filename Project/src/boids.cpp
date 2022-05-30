#include "boids.hpp"
#define _USE_MATH_DEFINES
#include <random>
#include <cmath>
#include <iostream>

//Boid constructor
Boid::Boid(){
    position= cgp::vec3{cgp::rand_interval(-border_x,border_x),cgp::rand_interval(-border_y,border_y),cgp::rand_interval(-border_z,border_z)};
    vitesse= cgp::vec3{cgp::rand_interval(-10.0,10.0),cgp::rand_interval(-10.0,10.0),cgp::rand_interval(-10.0,10.0)};
}

float Boid::distance_to(Boid b){
    return sqrt(pow(position.x-b.position.x,2)+pow(position.y-b.position.y,2)+pow(position.z-b.position.z,2));
}

void Boid::draw_boid(float dt){
    //Evite les collision avec le cube
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

    position= position + vitesse*dt*20;
}

std::vector<Boid *> initialize_boids(){
    std::vector<Boid *> boids;
    boids.resize(number_boids);
    for (int i = 0; i < number_boids; i++)
    {
       (boids[i]) = new Boid();
    }
    return boids;
}

//! Separation
//* Evite les collisions entre boids
void separation(std::vector<Boid *> boids){
    for (int i = 0; i < number_boids; i++)
    {   
        for (int j = 0; j < number_boids; j++)
        {
            if (j!=i)
            {
                float d= boids[i]->distance_to(*(boids[j]));
                if (d<10.0)
                {//TODO ste
                    cgp::vec3 dir= boids[j]->position-boids[i]->position;
                    cgp::vec3 norm_dir = dir/ sqrt(dir.x*dir.x+dir.y*dir.y+dir.z*dir.z);
                    boids[i]->vitesse = cgp::normalize(boids[i]->vitesse)+(norm_dir)*(0.01/(d+0.00001) -1/(10.0*10.0));
                             
                }  
            }
        }
    }
}
//! Alignment
//* Calul la vitesse moyenne des voisin d'un boid et applique la moyenne au mouvement
void alignment(std::vector<Boid *> boids){
    for (int i = 0; i < number_boids; i++)
    {   
        cgp::vec3 v={0,0,0};
        int nb=0;
        for (int j = 0; j < number_boids; j++)
        {
            if (j!=i)
            {
                float d= boids[i]->distance_to(*(boids[j]));
                if(d<30.0){
                    v+= boids[j]-> vitesse ;
                    nb+=1;  
                }        
            }
            if(nb!=0){
                v= v/((float)nb);
                boids[i]->vitesse =cgp::normalize(boids[i]->vitesse)+  v*0.001;
            }
        }
    }
}
//! Cohesion
//* Trouve la position du centre des voisins du boid et l'oriente vers celui-ci
void cohesion(std::vector<Boid *> boids){
    for (int i = 0; i < number_boids; i++)
    {   
        cgp::vec3 p={0,0,0};
        int nb=0;
        for (int j = 0; j < number_boids; j++)
        {
            
            float d= boids[i]->distance_to(*(boids[j]));
            if(d<30.0){
                p+= boids[j]-> position ;
                nb+=1;  
            }        
            
            if(nb!=0){
                p= p/((float)nb);
                boids[i]->vitesse =cgp::normalize(boids[i]->vitesse)+(p-boids[i]->position)*0.00001;
            }
        }
    }
}