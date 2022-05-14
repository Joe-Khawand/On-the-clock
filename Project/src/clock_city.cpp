#include "clock_city.hpp"
#include "cmath"

using namespace cgp;


mesh create_arrow_mesh(float h)
{
    mesh m; 
    int N = 20;
    m.position.resize(N);
    m.position[0]=vec3{0,-0.5,0};
    m.position[1]=vec3{0,-0.5,h};
    m.position[2]=vec3{5.0,-0.5,0};
    m.position[3]=vec3{5.0,-0.5,h};
    m.position[4]=vec3{4.0,-1.5,0};
    m.position[5]=vec3{4.0,-1.5,h};
    m.position[6]=vec3{4.0+(std::sqrt(2))/2.0,-1.5-(std::sqrt(2.0))/2.0,0};
    m.position[7]=vec3{4.0+(std::sqrt(2))/2.0,-1.5-(std::sqrt(2.0))/2.0,h};
    m.position[8]=vec3{7.0,0,0};
    m.position[9]=vec3{7.0,0,h};
    m.position[10]=vec3{4.0+(std::sqrt(2))/2.0,1.5+(std::sqrt(2.0))/2.0,0};
    m.position[11]=vec3{4.0+(std::sqrt(2))/2.0,1.5+(std::sqrt(2.0))/2.0,h};
    m.position[12]=vec3{4.0,1.5,0};
    m.position[13]=vec3{4.0,1.5,h};
    m.position[14]=vec3{5.0,0.5,0};
    m.position[15]=vec3{5.0,0.5,h};
    m.position[16]=vec3{0,0.5,0};
    m.position[17]=vec3{0,0.5,h};
    m.position[18]=vec3{0,0,0};
    m.position[19]=vec3{0,0,h};
    for(int i=0; i<N; i=i+2)
    {
        m.connectivity.push_back((uint3{i%N, (i+1)%N, (i+2)%N}));
        m.connectivity.push_back((uint3{(i+1)%N, (i+3)%N, (i+2)%N}));
    }
    m.connectivity.push_back(uint3{0,14,2});
    m.connectivity.push_back(uint3{0,16,14});
    m.connectivity.push_back(uint3{1,15,3});
    m.connectivity.push_back(uint3{1,17,15});
    m.connectivity.push_back(uint3{2,14,8});
    m.connectivity.push_back(uint3{3,15,9});
    m.connectivity.push_back(uint3{6,2,8});
    m.connectivity.push_back(uint3{7,3,9});
    m.connectivity.push_back(uint3{4,2,6});
    m.connectivity.push_back(uint3{5,3,7});
    m.connectivity.push_back(uint3{8,14,10});
    m.connectivity.push_back(uint3{9,15,11});
    m.connectivity.push_back(uint3{10,14,12});
    m.connectivity.push_back(uint3{11,15,13});

    m.fill_empty_field();
    return m;
}

mesh create_ring(float r){
    return mesh_primitive_torus(r,0.5,vec3{0,0,0},vec3{0,0,1});
}

mesh create_cone_mesh(float radius, float height, float z_offset)
{
    mesh m; 
    // To do: fill this mesh ...
    // ...
    int N = 9;
    m.position.resize(N + 3);
    m.uv.resize(N+3);
    m.position[N+1] = vec3{0.f, 0.f, z_offset};
    m.position[N+2] = vec3{0.f, 0.f, height + z_offset};
    for(int i=0; i<N+1; i++)
    {
        float x = radius * std::cos(i * 2.0f * M_PI / N);
        float y = radius * std::sin(i * 2.0f * M_PI / N);
        m.position[i] = vec3{x, y, z_offset};
        m.uv[i]= {2.f * (i%2), 4.f};
    }
    for(int i=0; i<N; i++)
    {
        m.connectivity.push_back(uint3{N+1, i, i+1});
        m.connectivity.push_back(uint3{i, i+1, N+2});
    }

    m.fill_empty_field();
    return m;
}


mesh create_tree_foliage()
{
    float h = 0.7f; // trunk height
    float r = 0.1f; // trunk radius

    // Create a green foliage from 3 cones
    mesh foliage = create_cone_mesh(4*r, 6*r, 0.0f);      // base-cone
    foliage.push_back(create_cone_mesh(4*r, 6*r, 2*r));   // middle-cone
    foliage.push_back(create_cone_mesh(4*r, 6*r, 4*r));   // top-cone
    foliage.position += vec3(0,0,h);                 // place foliage at the top of the trunk
    //foliage.color.fill({0.4f, 0.6f, 0.3f});

    return foliage;
}


mesh create_shroom_cap()
{
    float h = 0.1f; // trunk height
    float r = 0.01f; // trunk radius

    // Create a red hat from 1 cone
    mesh hat = create_cone_mesh(5*r, 3*r, 0.0f);
    hat.position += vec3(0,0,h);                 // place foliage at the top of the trunk
    //hat.color.fill({1.f, 0.3f, 0.3f});
    for(vec2& p : hat.uv) p = 0.2f * p;

    return hat;
}
