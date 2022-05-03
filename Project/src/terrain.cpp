
#include "terrain.hpp"


using namespace cgp;

void update_terrain(mesh& terrain, mesh_drawable& terrain_visual, perlin_noise_parameters const& parameters, float terrain_length)
{
    // Number of samples in each direction (assuming a square grid)
    int const N = std::sqrt(terrain.position.size());

    // Recompute the new vertices
    for (int ku = 0; ku < N; ++ku) {
        for (int kv = 0; kv < N; ++kv) {

            // Compute local parametric coordinates (u,v) \in [0,1]
            const float u = ku/(N-1.0f);
            const float v = kv/(N-1.0f);

            int const idx = ku*N+kv;

            // Compute the Perlin noise
            float const noise = noise_perlin({u, v}, parameters.octave, parameters.persistency, parameters.frequency_gain);

            // use the noise as height value
            terrain.position[idx].z = parameters.terrain_height*noise + evaluate_terrain_height((u - 0.5f) * terrain_length, (v - 0.5f) * terrain_length);

            // use also the noise as color value
            terrain.color[idx] = 0.3f*vec3(0,0.5f,0)+0.7f*noise*vec3(1,1,1);
        }
    }

    // Update the normal of the mesh structure
    terrain.compute_normal();

    // Update step: Allows to update a mesh_drawable without creating a new one
    terrain_visual.update_position(terrain.position);
    terrain_visual.update_normal(terrain.normal);
    terrain_visual.update_color(terrain.color);

}

// Evaluate 3D position of the terrain for any (u,v) \in [0,1]
float evaluate_terrain_height(float x, float y)
{
    //vec2 p_0 = { 0, 0 };
    //float h_0 = 2.0f;
    //float sigma_0 = 3.0f;
    vec2 p_i[4] = { {-10,-10}, {5,5}, {-3,4}, {6,4} };
    float h_i[4] = {3.0f, -1.5f, 1.0f, 2.0f};
    float sigma_i[4] = {10.f, 3.0f, 4.f, 4.f};

    float z = 0.f;

    for(int i=0; i<4; i++)
    {
        float d = norm(vec2(x, y) - p_i[i]) / sigma_i[i];

        z += h_i[i] * std::exp(-d * d);
    }

    return z;
}

mesh create_terrain_mesh(int N, float terrain_length)
{

    mesh terrain; // temporary terrain storage (CPU only)
    terrain.position.resize(N*N);
    terrain.uv.resize(N*N);

    // Fill terrain geometry
    for(int ku=0; ku<N; ++ku)
    {
        for(int kv=0; kv<N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            float u = ku/(N-1.0f);
            float v = kv/(N-1.0f);

            // Compute the real coordinates (x,y) of the terrain 
            float x = (u - 0.5f) * terrain_length;
            float y = (v - 0.5f) * terrain_length;

            // Compute the surface height function at the given sampled coordinate
            float z = evaluate_terrain_height(x, y);

            // Store vertex coordinates
            terrain.position[kv+N*ku] = {x,y,z};
            terrain.uv[kv+N*ku] = {20 * u, 20 * v};
        }
    }

    // Generate triangle organization
    //  Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    for(int ku=0; ku<N-1; ++ku)
    {
        for(int kv=0; kv<N-1; ++kv)
        {
            unsigned int idx = kv + N*ku; // current vertex offset

            uint3 triangle_1 = {idx, idx+1+N, idx+1};
            uint3 triangle_2 = {idx, idx+N, idx+1+N};

            terrain.connectivity.push_back(triangle_1);
            terrain.connectivity.push_back(triangle_2);
        }
    }

    // need to call this function to fill the other buffer with default values (normal, color, etc)
	terrain.fill_empty_field(); 

    return terrain;
}

std::vector<cgp::vec3> generate_positions_on_terrain(int N, float terrain_length)
{
    std::vector<cgp::vec3> pi;
    for(int i = 0; i<N; i++){
        float x = rand_interval(-0.5f * terrain_length, 0.5f * terrain_length);
        float y = rand_interval(-0.5f * terrain_length, 0.5f * terrain_length);
        bool boo = true;
        for(vec3 p : pi){
            if(norm(vec2(x, y) - p.xy()) < 0.8f)
                boo = false;
        }
        if(boo)
            pi.push_back({x, y, evaluate_terrain_height(x, y)});
        else
            i--;
    }
    return pi;
}

std::vector<cgp::vec3> generate_positions_mushrooms(int N, float terrain_length, std::vector<cgp::vec3> pi)
{
    std::vector<cgp::vec3> qi;
    for(int i = 0; i<N; i++){
        float x = rand_interval(-0.5f * terrain_length, 0.5f * terrain_length);
        float y = rand_interval(-0.5f * terrain_length, 0.5f * terrain_length);
        bool boo = true;
        for(vec3 p : pi){
            if(norm(vec2(x, y) - p.xy()) < 0.15f)
                boo = false;
        }
        for(vec3 q : qi){
            if(norm(vec2(x, y) - q.xy()) < 0.1f)
                boo = false;
        }
        if(boo)
            qi.push_back({x, y, evaluate_terrain_height(x, y)});
        else
            i--;
    }
    return qi;
}

