#include "tree.hpp"
#include "cmath"

using namespace cgp;


mesh create_cylinder_mesh(float radius, float height)
{
    mesh m; 
    // To do: fill this mesh ...
    // ...
    // To add a position: 
    //   m.position.push_back(vec3{x,y,z})
    // Or in pre-allocating the buffer:
    //   m.position.resize(maximalSize);
    //   m.position[index] = vec3{x,y,z}; (with 0<= index < maximalSize)
    // 
    // Similar with the triangle connectivity:
    //  m.connectivity.push_back(uint3{index_1, index_2, index_3});
    int N = 18;
    m.position.resize(N + 2);
    m.uv.resize(N+2);

    for(int i=0; i<N + 2; i++)
    {
        float x = radius * std::cos((i/2) * 2.0f * M_PI / (N/2));
        float y = radius * std::sin((i/2) * 2.0f * M_PI / (N/2));
        float z;
        if(i%2 == 1) z = height;
        else z = 0.f;
        m.position[i] = vec3{x, y, z};
        m.uv[i]= {1.f * i / N, z};
    }

    for(int i=0; i<N; i+=2)
    {
        m.connectivity.push_back((uint3{i+1, i, (i+2)}));
        m.connectivity.push_back((uint3{(i+3), i+1, (i+2)}));
    }
    // Need to call fill_empty_field() before returning the mesh 
    //  this function fill all empty buffer with default values (ex. normals, colors, etc).
    m.fill_empty_field();

    return m;
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

mesh create_tree()
{
    float h = 0.7f; // trunk height
    float r = 0.1f; // trunk radius

    // Create a brown trunk
    mesh trunk = create_cylinder_mesh(r, h);
    trunk.color.fill({0.4f, 0.3f, 0.3f});


    // Create a green foliage from 3 cones
    mesh foliage = create_cone_mesh(4*r, 6*r, 0.0f);      // base-cone
    foliage.push_back(create_cone_mesh(4*r, 6*r, 2*r));   // middle-cone
    foliage.push_back(create_cone_mesh(4*r, 6*r, 4*r));   // top-cone
    foliage.position += vec3(0,0,h);                 // place foliage at the top of the trunk
    foliage.color.fill({0.4f, 0.6f, 0.3f});

    // The tree is composted of the trunk and the foliage
    mesh tree = trunk;
    tree.push_back(foliage);

    return tree;
}

mesh create_tree_trunk()
{
    float h = 0.7f; // trunk height
    float r = 0.1f; // trunk radius

    // Create a brown trunk
    mesh trunk = create_cylinder_mesh(r, h);
    trunk.color.fill({0.4f, 0.3f, 0.3f});
    return trunk;
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

mesh create_shroom()
{
    float h = 0.1f; // trunk height
    float r = 0.01f; // trunk radius

    // Create a beige stump
    mesh trunk = create_cylinder_mesh(r, h);
    trunk.color.fill({1.f, 0.8f, 0.8f});


    // Create a red hat from 1 cone
    mesh hat = create_cone_mesh(5*r, 3*r, 0.0f);
    hat.position += vec3(0,0,h);                 // place foliage at the top of the trunk
    hat.color.fill({1.f, 0.3f, 0.3f});

    // The tree is composted of the stump and the hat
    mesh shroom = trunk;
    shroom.push_back(hat);

    return shroom;
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

mesh create_shroom_stump()
{
    float h = 0.1f; // trunk height
    float r = 0.01f; // trunk radius

    // Create a beige stump
    mesh stump = create_cylinder_mesh(r, h);
    stump.color.fill({1.f, 0.8f, 0.8f});
    return stump;
}
