#include "clock_city.hpp"
#define _USE_MATH_DEFINES
#include "cmath"

using namespace cgp;


// mesh create_arrow_mesh(float h)
// {
//     mesh m; 
//     int N = 20;
//     m.position.resize(N);
//     m.position[0]=vec3{0,-0.5,0};
//     m.position[1]=vec3{0,-0.5,h};
//     m.position[2]=vec3{5.0,-0.5,0};
//     m.position[3]=vec3{5.0,-0.5,h};
//     m.position[4]=vec3{4.0,-1.5,0};
//     m.position[5]=vec3{4.0,-1.5,h};
//     m.position[6]=vec3{4.0+(std::sqrt(2))/2.0,-1.5-(std::sqrt(2.0))/2.0,0};
//     m.position[7]=vec3{4.0+(std::sqrt(2))/2.0,-1.5-(std::sqrt(2.0))/2.0,h};
//     m.position[8]=vec3{7.0,0,0};
//     m.position[9]=vec3{7.0,0,h};
//     m.position[10]=vec3{4.0+(std::sqrt(2))/2.0,1.5+(std::sqrt(2.0))/2.0,0};
//     m.position[11]=vec3{4.0+(std::sqrt(2))/2.0,1.5+(std::sqrt(2.0))/2.0,h};
//     m.position[12]=vec3{4.0,1.5,0};
//     m.position[13]=vec3{4.0,1.5,h};
//     m.position[14]=vec3{5.0,0.5,0};
//     m.position[15]=vec3{5.0,0.5,h};
//     m.position[16]=vec3{0,0.5,0};
//     m.position[17]=vec3{0,0.5,h};
//     m.position[18]=vec3{0,0,0};
//     m.position[19]=vec3{0,0,h};
//     for(int i=0; i<N; i=i+2)
//     {
//         m.connectivity.push_back((uint3{i%N, (i+1)%N, (i+2)%N}));
//         m.connectivity.push_back((uint3{(i+1)%N, (i+3)%N, (i+2)%N}));
//     }
//     m.connectivity.push_back(uint3{0,14,2});
//     m.connectivity.push_back(uint3{0,16,14});
//     m.connectivity.push_back(uint3{1,15,3});
//     m.connectivity.push_back(uint3{1,17,15});
//     m.connectivity.push_back(uint3{2,14,8});
//     m.connectivity.push_back(uint3{3,15,9});
//     m.connectivity.push_back(uint3{6,2,8});
//     m.connectivity.push_back(uint3{7,3,9});
//     m.connectivity.push_back(uint3{4,2,6});
//     m.connectivity.push_back(uint3{5,3,7});
//     m.connectivity.push_back(uint3{8,14,10});
//     m.connectivity.push_back(uint3{9,15,11});
//     m.connectivity.push_back(uint3{10,14,12});
//     m.connectivity.push_back(uint3{11,15,13});

//     m.fill_empty_field();
//     return m;
// }

mesh create_arrow_mesh(float h, float l, float w)
{
    mesh m;
    int N = 18;
    float x = std::sqrt(2) / 2.0f;
    m.position.resize(3 * N);

    m.position[0]=vec3{0, -0.5 * w, 0};
    m.position[1]=vec3{0, -0.5 * w, h};
    m.position[2]=vec3{l - (0.5 + 2.0 * x) * w, -0.5 * w, 0};
    m.position[3]=vec3{l - (0.5 + 2.0 * x) * w, -0.5 * w, h};
    m.position[4]=vec3{l - (1.5 + 2.0 * x) * w, -1.5 * w, 0};
    m.position[5]=vec3{l - (1.5 + 2.0 * x) * w, -1.5 * w, h};
    m.position[6]=vec3{l - (1.5 + x) * w, -(1.5 + x) * w, 0};
    m.position[7]=vec3{l - (1.5 + x) * w, -(1.5 + x) * w, h};
    m.position[8]=vec3{l, 0, 0};
    m.position[9]=vec3{l, 0, h};
    m.position[10]=vec3{l - (1.5 + x) * w, (1.5 + x) * w, 0};
    m.position[11]=vec3{l - (1.5 + x) * w, (1.5 + x) * w, h};
    m.position[12]=vec3{l - (1.5 + 2.0 * x) * w, 1.5 * w, 0};
    m.position[13]=vec3{l - (1.5 + 2.0 * x) * w, 1.5 * w, h};
    m.position[14]=vec3{l - (0.5 + 2.0 * x) * w, 0.5 * w, 0};
    m.position[15]=vec3{l - (0.5 + 2.0 * x) * w, 0.5 * w, h};
    m.position[16]=vec3{0, 0.5 * w, 0};
    m.position[17]=vec3{0, 0.5 * w, h};

    for (int i = 0; i < N; i ++) {
        m.position[N + i] = m.position[i];
        m.position[2*N + i] = m.position[i];
    }

    // building lateral sides
    for(int i=2; i<N; i=i+2)
    {
        if (i%4 == 0)
        {
            m.connectivity.push_back(uint3{2 * N + (i%N), 2 * N + ((i+1)%N), 2 * N + ((i+2)%N)});
            m.connectivity.push_back(uint3{2 * N + ((i+1)%N), 2 * N + ((i+3)%N), 2 * N + ((i+2)%N)});
        }
        else
        {
            m.connectivity.push_back(uint3{N + (i%N), N + ((i+1)%N), N + ((i+2)%N)});
            m.connectivity.push_back(uint3{N + ((i+1)%N), N + ((i+3)%N), N + ((i+2)%N)});
        }
    }

    m.connectivity.push_back(uint3{N, N+1, 2*N+2});
    m.connectivity.push_back(uint3{N+1, 2*N+3, 2*N+2});

    //building top and bottom sides
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

// mesh create_cylinder(float r1,float r2,float height){
//     //r1 big radius, r2 small
//     int nu= 2;
//     int nv=70;
//     mesh m= mesh_primitive_cylinder(r1,vec3(0,0,0),vec3(0,0,height),nu,nv,false);
//     m.push_back(mesh_primitive_cylinder(r2,vec3(0,0,0),vec3(0,0,height),nu,nv,false));
//     int size= nu*nv;
//     for (int i = 0; i < size; i=i+1)
//     {
//         uint3 triangle_1 ={i%(2*size),(i+size)%(2*size), (i+1)%(2*size)};
//         uint3 triangle_2 ={(i+size)%(2*size), (i+1+size)%(2*size), (i+1)%(2*size)};
//         m.connectivity.push_back(triangle_1);
//         m.connectivity.push_back(triangle_2);
//     }
//     m.fill_empty_field();
//     return m;
    
// }

// radius_1 > radius_2
mesh create_cylinder(float r1,float r2,float height){
    //r1 big radius, r2 small
    int nu= 2;
    int nv=70;
    mesh m= mesh_primitive_cylinder(r1,vec3(0,0,0),vec3(0,0,height),nu,nv,false);
    m.push_back(mesh_primitive_cylinder(r2,vec3(0,0,0),vec3(0,0,height),nu,nv,false));
    int size= nu*nv;
    m.position.resize(4 * size);
    for (int i = 0; i < 2 * size; i=i+1) {
        m.position[2 * size + i] = m.position[i];
    }
    for (int i = 0; i < size/2; i=i+1)
    {
        uint3 triangle_1 ={2 * size + i, 2 * size + (i+size), 2 * size + (i+1)%(size/2)};
        uint3 triangle_2 ={2 * size + (i+size)%(2*size), 2 * size + ((i+1)%(size/2)+size)%(2*size), 2 * size + (i+1)%(size/2)};
        m.connectivity.push_back(triangle_1);
        m.connectivity.push_back(triangle_2);
    }
    for (int i = 0; i < size/2; i=i+1)
    {
        uint3 triangle_1 ={2 * size + i + size/2, 2 * size + (i+size) + size/2, 2 * size + (i+1)%(size/2) + size/2};
        uint3 triangle_2 ={2 * size + (i+size + size/2)%(2*size), 2 * size + ((i+1)%(size/2)+size + size/2)%(2*size), 2 * size + (i+1)%(size/2) + size/2};
        //uint3 triangle_1 ={2 * size + i, 2 * size + (i+size)%(2*size), 2 * size + (i+1)%(2*size)};
        //uint3 triangle_2 ={2 * size + (i+size)%(2*size), 2 * size + (i+1+size)%(2*size), 2 * size + (i+1)%(2*size)};
        m.connectivity.push_back(triangle_1);
        m.connectivity.push_back(triangle_2);
    }
    m.fill_empty_field();
    return m; 
}

// Initializes city and creates hierarchy
cgp::hierarchy_mesh_drawable initialize_city(city_struct city)
{
    //TODO instancing???? (instead of this shite)

    mesh arrow_mesh = create_arrow_mesh(0.2, 7.0, 1.0);
    city.arrow.initialize(arrow_mesh, "Arrow");
	city.arrow.transform.scaling=10.0;

	mesh building_mesh = mesh_load_file_obj("assets/Objects/Building.obj");
	city.building.initialize(building_mesh,"building_obj");
	city.building_2.initialize(building_mesh,"building_obj_2");
	city.building_3.initialize(building_mesh,"building_obj_3");
	city.building_4.initialize(building_mesh,"building_obj_4");
	city.building_5.initialize(building_mesh,"building_obj_5");
	city.building_6.initialize(building_mesh,"building_obj_6");
	city.building_7.initialize(building_mesh,"building_obj_7");
	city.building_8.initialize(building_mesh,"building_obj_8");
	city.building_9.initialize(building_mesh,"building_obj_9");
	city.building_10.initialize(building_mesh,"building_obj_10");
    city.building.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building.transform.scaling=0.2;
	city.building_2.transform.scaling=0.2;
	city.building_2.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_3.transform.scaling=0.2;
	city.building_3.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_4.transform.scaling=0.2;
	city.building_4.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_5.transform.scaling=0.2;
	city.building_5.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_6.transform.scaling=0.2;
	city.building_6.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_7.transform.scaling=0.2;
	city.building_7.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_8.transform.scaling=0.2;
	city.building_8.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_9.transform.scaling=0.2;
	city.building_9.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	city.building_10.transform.scaling=0.2;
	city.building_10.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);

	mesh nuclear_mesh = mesh_load_file_obj("assets/Objects/Nuclear_Cooling_Tower.obj");
	city.nuclear.initialize(nuclear_mesh,"nuclear_obj");
	city.nuclear.transform.scaling=0.0023;
	
	city.city_hierarchy.add(city.arrow);
	city.city_hierarchy.add(city.building,"Arrow",{1.2,3.5,2});
	city.city_hierarchy.add(city.building_2,"Arrow",{1.2,1.5,2});
	city.city_hierarchy.add(city.building_3,"Arrow",{1.2,-0.5,2});
	city.city_hierarchy.add(city.building_4,"Arrow",{3.2,3.5,2});
	city.city_hierarchy.add(city.building_5,"Arrow",{3.2,-3.5,2});
	city.city_hierarchy.add(city.building_6,"Arrow",{5.2,-3.5,2});
	city.city_hierarchy.add(city.building_7,"Arrow",{34,-2.5,2});
	city.city_hierarchy.add(city.building_8,"Arrow",{34,2.5,2});
	city.city_hierarchy.add(city.building_9,"Arrow",{24,-2.5,2});
	city.city_hierarchy.add(city.building_10,"Arrow",{29,2.5,2});
	city.city_hierarchy.add(city.nuclear,"Arrow",{60,0,2});

    return city.city_hierarchy;
}