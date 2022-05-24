#include "clock_city.hpp"
#define _USE_MATH_DEFINES
#include "cmath"

using namespace cgp;

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


cgp::hierarchy_mesh_drawable initialize_hours()
{
    cgp::hierarchy_mesh_drawable city_hierarchy;
    mesh_drawable exterior_cylinder;
    mesh_drawable cylinder;
    mesh_drawable arrow;

    mesh_drawable city;
    // mesh_drawable nuclear;
    // mesh_drawable building;
    // mesh_drawable building_2;
    // mesh_drawable building_3;
    // mesh_drawable building_4;
    // mesh_drawable building_5;
    // mesh_drawable building_6;
    // mesh_drawable building_7;
    // mesh_drawable building_8;
    // mesh_drawable building_9;
    // mesh_drawable building_10;

    cylinder.initialize(create_cylinder(16, 14.0, 2.0), "Cylinder");
    exterior_cylinder.initialize(create_cylinder(78, 75.0, 2.0), "Exterior");

    arrow.initialize(create_arrow_mesh(1.0, 50, 6.5), "Arrow");
    city.initialize(create_city(1, 1, 0.1, 31, 6, 7), "City");
	//arrow.transform.scaling=10.0;

	// mesh building_mesh = mesh_load_file_obj("assets/Objects/Building.obj");
	// building.initialize(building_mesh,"building_obj");
	// building_2.initialize(building_mesh,"building_obj_2");
	// building_3.initialize(building_mesh,"building_obj_3");
	// building_4.initialize(building_mesh,"building_obj_4");
	// building_5.initialize(building_mesh,"building_obj_5");
	// building_6.initialize(building_mesh,"building_obj_6");
	// building_7.initialize(building_mesh,"building_obj_7");
	// building_8.initialize(building_mesh,"building_obj_8");
	// building_9.initialize(building_mesh,"building_obj_9");
	// building_10.initialize(building_mesh,"building_obj_10");
    // building.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building.transform.scaling=0.2;
	// building_2.transform.scaling=0.2;
	// building_2.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_3.transform.scaling=0.2;
	// building_3.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_4.transform.scaling=0.2;
	// building_4.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_5.transform.scaling=0.2;
	// building_5.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_6.transform.scaling=0.2;
	// building_6.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_7.transform.scaling=0.2;
	// building_7.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_8.transform.scaling=0.2;
	// building_8.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_9.transform.scaling=0.2;
	// building_9.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);
	// building_10.transform.scaling=0.2;
	// building_10.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, M_PI_2);

	// mesh nuclear_mesh = mesh_load_file_obj("assets/Objects/Nuclear_Cooling_Tower.obj");
	// nuclear.initialize(nuclear_mesh,"nuclear_obj");
	// nuclear.transform.scaling=0.0023;
	
    city_hierarchy.add(exterior_cylinder);
    city_hierarchy.add(cylinder, "Exterior");
	city_hierarchy.add(arrow, "Cylinder", {14, 0, 0.5});
    city_hierarchy.add(city, "Arrow", {2, -3.25, 1});
	// city_hierarchy.add(building,"Arrow",{1.2,3.5,2});
	// city_hierarchy.add(building_2,"Arrow",{1.2,1.5,2});
	// city_hierarchy.add(building_3,"Arrow",{1.2,-0.5,2});
	// city_hierarchy.add(building_4,"Arrow",{3.2,3.5,2});
	// city_hierarchy.add(building_5,"Arrow",{3.2,-3.5,2});
	// city_hierarchy.add(building_6,"Arrow",{5.2,-3.5,2});
	// city_hierarchy.add(building_7,"Arrow",{34,-2.5,2});
	// city_hierarchy.add(building_8,"Arrow",{34,2.5,2});
	// city_hierarchy.add(building_9,"Arrow",{24,-2.5,2});
	// city_hierarchy.add(building_10,"Arrow",{29,2.5,2});
	// city_hierarchy.add(nuclear,"Arrow",{60,0,2});

    city_hierarchy["Cylinder"].transform.translation = {0, 0, -2};
    city_hierarchy.update_local_to_global_coordinates();
    return city_hierarchy;
}

cgp::hierarchy_mesh_drawable initialize_minutes()
{
    cgp::hierarchy_mesh_drawable city_hierarchy;
    mesh_drawable exterior_cylinder;
    mesh_drawable cylinder;
    mesh_drawable arrow;
    mesh_drawable city;

    cylinder.initialize(create_cylinder(11, 5, 2.0), "Cylinder");
    exterior_cylinder.initialize(create_cylinder(118, 115.0, 2.0), "Exterior");    

    arrow.initialize(create_arrow_mesh(1, 95, 6.5), "Arrow");
    city.initialize(create_city(1, 1, 0.1, 70, 6, 7), "City");
	
    city_hierarchy.add(exterior_cylinder);
    city_hierarchy.add(cylinder, "Exterior");
	city_hierarchy.add(arrow, "Cylinder", {5, 0, 0.5});
    city_hierarchy.add(city, "Arrow", {6, -3.25, 1});

    city_hierarchy["Exterior"].transform.translation = {0, 0, -25};
    city_hierarchy.update_local_to_global_coordinates();
    return city_hierarchy;
}

cgp::hierarchy_mesh_drawable initialize_seconds()
{
    cgp::hierarchy_mesh_drawable city_hierarchy;
    mesh_drawable exterior_cylinder;
    mesh_drawable exterior_base;
    mesh_drawable cylinder;
    mesh_drawable arrow;
    mesh_drawable city;

    cylinder.initialize(create_cylinder(22, 20.0, 2.0), "Cylinder");
    exterior_base.initialize(create_cylinder(154, 104.5, 2), "Base");
    mesh exterior_mesh = create_cylinder(140, 110, 2.0);
    for (int i = 0; i < 70; i++)
    {
        exterior_mesh.position[140 + i] *= 0.95;
        exterior_mesh.position[280 + 140 + i] *= 0.95;
        exterior_mesh.position[i] *= 1.1;
        exterior_mesh.position[280 + i] *= 1.1;
    }
    exterior_mesh.normal.clear();
    exterior_mesh.fill_empty_field();

    exterior_cylinder.initialize(exterior_mesh, "Exterior");

    arrow.initialize(create_arrow_mesh(1, 80, 3.2), "Arrow");
    city.initialize(create_city(1, 1, 0.1, 70, 3, 7), "City");
	
    city_hierarchy.add(exterior_cylinder);
    city_hierarchy.add(exterior_base, "Exterior", {0, 0, -2});
    city_hierarchy.add(cylinder, "Exterior", {0, 0, -1});
	city_hierarchy.add(arrow, "Cylinder", {20, 0, 0.5});
    city_hierarchy.add(city, "Arrow", {2, -1.6, 1});

    mesh_drawable one;
    one.initialize(brick(20, 2, 2), "One");
    one.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - M_PI / 6);
    city_hierarchy.add(one, "Exterior", {115 * std::cos(M_PI / 6), - 115 * std::sin(M_PI / 6), 2});

    mesh_drawable two;
    mesh two_mesh;
    two_mesh.push_back(brick(20, 2, 2, {0, -2, 0}));
    two_mesh.push_back(brick(20, 2, 2, {0, 2, 0}));
    two.initialize(two_mesh, "Two");
    two.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 2*M_PI / 6);
    city_hierarchy.add(two, "Exterior", {115 * std::cos(2 * M_PI / 6), - 115 * std::sin(2 * M_PI / 6), 2});

    mesh_drawable three;
    mesh three_mesh;
    three_mesh.push_back(brick(20, 2, 2));
    three_mesh.push_back(brick(20, 2, 2, {0, -4, 0}));
    three_mesh.push_back(brick(20, 2, 2, {0, 4, 0}));
    three.initialize(three_mesh, "Three");
    three.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 3*M_PI / 6);
    city_hierarchy.add(three, "Exterior", {115 * std::cos(3 * M_PI / 6), - 115 * std::sin(3 * M_PI / 6), 2});

    mesh_drawable four;
    mesh four_mesh;
    four_mesh.push_back(brick(20, 2, 2, {0, 7, 0}));
    four_mesh.push_back(v(20, 2, 2, {0, -2, 0}));
    four.initialize(four_mesh, "Four");
    four.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 4*M_PI / 6);
    city_hierarchy.add(four, "Exterior", {115 * std::cos(4 * M_PI / 6), - 115 * std::sin(4 * M_PI / 6), 2});

    mesh_drawable five;
    mesh five_mesh;
    five_mesh.push_back(v(20, 2, 2));
    five.initialize(five_mesh, "Five");
    five.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 5*M_PI / 6);
    city_hierarchy.add(five, "Exterior", {115 * std::cos(5 * M_PI / 6), - 115 * std::sin(5 * M_PI / 6), 2});

    mesh_drawable six;
    mesh six_mesh;
    six_mesh.push_back(brick(20, 2, 2, {0, -7, 0}));
    six_mesh.push_back(v(20, 2, 2, {0, 2, 0}));
    six.initialize(six_mesh, "Six");
    six.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 6*M_PI / 6);
    city_hierarchy.add(six, "Exterior", {115 * std::cos(6 * M_PI / 6), - 115 * std::sin(6 * M_PI / 6), 2});

    mesh_drawable seven;
    mesh seven_mesh;
    seven_mesh.push_back(brick(20, 2, 2, {0, -9, 0}));
    seven_mesh.push_back(brick(20, 2, 2, {0, -5, 0}));
    seven_mesh.push_back(v(20, 2, 2, {0, 4, 0}));
    seven.initialize(seven_mesh, "Seven");
    seven.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 7*M_PI / 6);
    city_hierarchy.add(seven, "Exterior", {115 * std::cos(7 * M_PI / 6), - 115 * std::sin(7 * M_PI / 6), 2});

    mesh_drawable eight;
    mesh eight_mesh;
    eight_mesh.push_back(brick(20, 2, 2, {0, -11, 0}));
    eight_mesh.push_back(brick(20, 2, 2, {0, -7, 0}));
    eight_mesh.push_back(brick(20, 2, 2, {0, -3, 0}));
    eight_mesh.push_back(v(20, 2, 2, {0, 6, 0}));
    eight.initialize(eight_mesh, "Eight");
    eight.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 8*M_PI / 6);
    city_hierarchy.add(eight, "Exterior", {115 * std::cos(8 * M_PI / 6), - 115 * std::sin(8 * M_PI / 6), 2});

    mesh_drawable nine;
    mesh nine_mesh;
    nine_mesh.push_back(brick(20, 2, 2, {0, 7, 0}));
    nine_mesh.push_back(x(20, 2, 2, {0, -2, 0}));
    nine.initialize(nine_mesh, "Nine");
    nine.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 9*M_PI / 6);
    city_hierarchy.add(nine, "Exterior", {115 * std::cos(9 * M_PI / 6), - 115 * std::sin(9 * M_PI / 6), 2});

    mesh_drawable ten;
    mesh ten_mesh;
    ten_mesh.push_back(x(20, 2, 2));
    ten.initialize(ten_mesh, "Ten");
    ten.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 10*M_PI / 6);
    city_hierarchy.add(ten, "Exterior", {115 * std::cos(10 * M_PI / 6), - 115 * std::sin(10 * M_PI / 6), 2});

    mesh_drawable eleven;
    mesh eleven_mesh;
    eleven_mesh.push_back(brick(20, 2, 2, {0, -7, 0}));
    eleven_mesh.push_back(x(20, 2, 2, {0, 2, 0}));
    eleven.initialize(eleven_mesh, "Eleven");
    eleven.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 11*M_PI / 6);
    city_hierarchy.add(eleven, "Exterior", {115 * std::cos(11 * M_PI / 6), - 115 * std::sin(11 * M_PI / 6), 2});

    mesh_drawable twelve;
    mesh twelve_mesh;
    twelve_mesh.push_back(brick(20, 2, 2, {0, -9, 0}));
    twelve_mesh.push_back(brick(20, 2, 2, {0, -5, 0}));
    twelve_mesh.push_back(x(20, 2, 2, {0, 4, 0}));
    twelve.initialize(twelve_mesh, "Twelve");
    twelve.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 12*M_PI / 6);
    city_hierarchy.add(twelve, "Exterior", {115 * std::cos(12 * M_PI / 6), - 115 * std::sin(12 * M_PI / 6), 2});
    

    city_hierarchy["Exterior"].transform.translation = {0, 0, -40};
    city_hierarchy.update_local_to_global_coordinates();
    return city_hierarchy;
}

cgp::mesh brick(float l, float w, float h, cgp::vec3 offset)
{
    mesh brick;
    brick.push_back(mesh_primitive_quadrangle({0, -w/2, 0}, {0, w/2, 0}, {0, w/2, h}, {0, -w/2, h}));
    brick.push_back(mesh_primitive_quadrangle({l, w/2, 0}, {l, -w/2, 0}, {l, -w/2, h}, {l, w/2, h}));
    brick.push_back(mesh_primitive_quadrangle({0, w/2, 0}, {l, w/2, 0}, {l, w/2, h}, {0, w/2, h}));
    brick.push_back(mesh_primitive_quadrangle({l, -w/2, 0}, {0, -w/2, 0}, {0, -w/2, h}, {l, -w/2, h}));
    brick.push_back(mesh_primitive_quadrangle({0, w/2, h}, {l, w/2, h}, {l, -w/2, h}, {0, -w/2, h}));
    brick.push_back(mesh_primitive_quadrangle({l, w/2, 0}, {0, w/2, 0}, {0, -w/2, 0}, {l, -w/2, 0}));
    for (int i = 0; i < brick.position.size(); i++) {
        brick.position[i] += offset;
    }
    brick.fill_empty_field();
    brick.color.fill({1,1,0});
    return brick;
}

cgp::mesh v(float l, float w, float h, cgp::vec3 offset)
{
    mesh v;
    v.push_back(mesh_primitive_quadrangle({0, -w/2, 0}, {0, w/2, 0}, {0, w/2, h}, {0, -w/2, h}));

    v.push_back(mesh_primitive_quadrangle({l, -2*w, 0}, {l, -3*w, 0}, {l, -3*w, h}, {l, -2*w, h}));
    v.push_back(mesh_primitive_quadrangle({0, w/2, 0}, {l, -2*w, 0}, {l, -2*w, h}, {0, w/2, h}));
    v.push_back(mesh_primitive_quadrangle({l, -3*w, 0}, {0, -w/2, 0}, {0, -w/2, h}, {l, -3*w, h}));
    v.push_back(mesh_primitive_quadrangle({0, w/2, h}, {l, -2*w, h}, {l, -3*w, h}, {0, -w/2, h}));
    v.push_back(mesh_primitive_quadrangle({l, -2*w, 0}, {0, w/2, 0}, {0, -w/2, 0}, {l, -3*w, 0}));

    v.push_back(mesh_primitive_quadrangle({l, 3*w, 0}, {l, 2*w, 0}, {l, 2*w, h}, {l, 3*w, h}));
    v.push_back(mesh_primitive_quadrangle({0, w/2, 0}, {l, 3*w, 0}, {l, 3*w, h}, {0, w/2, h}));
    v.push_back(mesh_primitive_quadrangle({l, 2*w, 0}, {0, -w/2, 0}, {0, -w/2, h}, {l, 2*w, h}));
    v.push_back(mesh_primitive_quadrangle({0, w/2, h}, {l, 3*w, h}, {l, 2*w, h}, {0, -w/2, h}));
    v.push_back(mesh_primitive_quadrangle({l, 3*w, 0}, {0, w/2, 0}, {0, -w/2, 0}, {l, 2*w, 0}));
    for (int i = 0; i < v.position.size(); i++) {
        v.position[i] += offset;
    }
    v.fill_empty_field();
    v.color.fill({1,1,0});
    return v;
}

cgp::mesh x(float l, float w, float h, cgp::vec3 offset)
{
    mesh x;
    x.push_back(mesh_primitive_quadrangle({0, 2*w, 0}, {0, 3*w, 0}, {0, 3*w, h}, {0, 2*w, h}));
    x.push_back(mesh_primitive_quadrangle({l, -2*w, 0}, {l, -3*w, 0}, {l, -3*w, h}, {l, -2*w, h}));
    x.push_back(mesh_primitive_quadrangle({0, 3*w, 0}, {l, -2*w, 0}, {l, -2*w, h}, {0, 3*w, h}));
    x.push_back(mesh_primitive_quadrangle({l, -3*w, 0}, {0, 2*w, 0}, {0, 2*w, h}, {l, -3*w, h}));
    x.push_back(mesh_primitive_quadrangle({0, 3*w, h}, {l, -2*w, h}, {l, -3*w, h}, {0, 2*w, h}));
    x.push_back(mesh_primitive_quadrangle({l, -2*w, 0}, {0, 3*w, 0}, {0, 2*w, 0}, {l, -3*w, 0}));

    x.push_back(mesh_primitive_quadrangle({0, -3*w, 0}, {0, -2*w, 0}, {0, -2*w, h}, {0, -3*w, h}));
    x.push_back(mesh_primitive_quadrangle({l, 3*w, 0}, {l, 2*w, 0}, {l, 2*w, h}, {l, 3*w, h}));
    x.push_back(mesh_primitive_quadrangle({0, -2*w, 0}, {l, 3*w, 0}, {l, 3*w, h}, {0, -2*w, h}));
    x.push_back(mesh_primitive_quadrangle({l, 2*w, 0}, {0, -3*w, 0}, {0, -3*w, h}, {l, 2*w, h}));
    x.push_back(mesh_primitive_quadrangle({0, -2*w, h}, {l, 3*w, h}, {l, 2*w, h}, {0, -3*w, h}));
    x.push_back(mesh_primitive_quadrangle({l, 3*w, 0}, {0, -2*w, 0}, {0, -3*w, 0}, {l, 2*w, 0}));
    for (int i = 0; i < x.position.size(); i++) {
        x.position[i] += offset;
    }
    x.fill_empty_field();
    x.color.fill({1,1,0});
    return x;
}

// Buildings of dimensions l x w with streets of width s
cgp::mesh create_city(float l, float w, float s, int nl, int nw, float hmax)
{
    mesh city;
    for (int i=0; i<nl; i++) {
        for (int j=0; j<nw; j++) {
            float h = rand_interval(0, (1 - (float) i / (float) nl) * (1 - (float) i / (float) nl) * hmax);
            //south face
            city.push_back(mesh_primitive_quadrangle({i*(l+s), j*(w+s), 0},
                                                    {i*(l+s) + l, j*(w+s), 0},
                                                    {i*(l+s) + l, j*(w+s), h},
                                                    {i*(l+s), j*(w+s), h}));
            
            //west face
            city.push_back(mesh_primitive_quadrangle({i*(l+s), j*(w+s) + w, 0},
                                                    {i*(l+s), j*(w+s), 0},
                                                    {i*(l+s), j*(w+s), h},
                                                    {i*(l+s), j*(w+s) + w, h}));
            
            //north face
            city.push_back(mesh_primitive_quadrangle({i*(l+s) + l, j*(w+s) + w, 0},
                                                    {i*(l+s), j*(w+s) + w, 0},
                                                    {i*(l+s), j*(w+s) + w, h},
                                                    {i*(l+s) + l, j*(w+s) + w, h}));
            
            //east face
            city.push_back(mesh_primitive_quadrangle({i*(l+s) + l, j*(w+s), 0},
                                                    {i*(l+s) + l, j*(w+s) + w, 0},
                                                    {i*(l+s) + l, j*(w+s) + w, h},
                                                    {i*(l+s) + l, j*(w+s), h}));
            
            //top face
            city.push_back(mesh_primitive_quadrangle({i*(l+s), j*(w+s), h},
                                                    {i*(l+s) + l, j*(w+s), h},
                                                    {i*(l+s) + l, j*(w+s) + w, h},
                                                    {i*(l+s), j*(w+s) + w, h}));
        }
    }
    return city;
}

float angle_increment(float t)
{
    float x = floorf(t);
    if (t-x < 0.75) return M_PI * x /6;
    else return M_PI * (x + 4 * (t-x-0.75)) / 6;
}