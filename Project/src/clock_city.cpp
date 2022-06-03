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
    m.uv.resize(4 * size);
    for (int i = 0; i < 2 * size; i=i+1) {

        m.uv[i] = vec2(height / 15 * m.uv[i].x, 2 * std::floor(r1 / 30) * m.uv[i].y);
    }
    for (int i = 0; i < 2 * size; i=i+1) {
        m.position[2 * size + i] = m.position[i];
        if(i<size)
            m.uv[2 * size + i] = vec2(std::floor((r2-r1) / 30),0) + m.uv[i];
        else
            m.uv[2 * size + i] = m.uv[i];
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

    cylinder.initialize(create_cylinder(16, 14.0, 2.0), "Cylinder");
    exterior_cylinder.initialize(create_cylinder(78, 75.0, 2.0), "Exterior");

    arrow.initialize(create_arrow_mesh(1.0, 50, 6.5), "Arrow");
    city.initialize(create_city(1, 1, 0.1, 31, 6, 7), "City");
	
    city_hierarchy.add(exterior_cylinder);
    city_hierarchy.add(cylinder, "Exterior");
	city_hierarchy.add(arrow, "Cylinder", {14, 0, 0.5});
    city_hierarchy.add(city, "Arrow", {2, -3.25, 1});

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
    // exterior_base.initialize(create_cylinder(154, 104.5, 2), "Base");
    // exterior_base.texture = opengl_load_texture_image("assets/color2.jpg",
    //     GL_REPEAT,
    //     GL_REPEAT);
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
    mesh base = create_cylinder(154, 104.5, 2);
    for (int i=0; i<base.position.size(); i++)
        base.position[i] += vec3(0, 0, -2);
    exterior_mesh.push_back(base);

    exterior_cylinder.initialize(exterior_mesh, "Exterior");
    exterior_cylinder.texture = opengl_load_texture_image("assets/wood2.jpg",
        GL_MIRRORED_REPEAT,
        GL_MIRRORED_REPEAT);

    arrow.initialize(create_arrow_mesh(1, 80, 3.2), "Arrow");
    city.initialize(create_city(1, 1, 0.1, 65, 3, 7), "City");
	
    city_hierarchy.add(exterior_cylinder);
    //city_hierarchy.add(exterior_base, "Exterior", {0, 0, -2});
    city_hierarchy.add(cylinder, "Exterior", {0, 0, -1});
	city_hierarchy.add(arrow, "Cylinder", {20, 0, 0.5});
    city_hierarchy.add(city, "Arrow", {2, -1.6, 1});

    GLuint number_texture = opengl_load_texture_image("assets/silver2.jpg",
        GL_MIRRORED_REPEAT,
        GL_MIRRORED_REPEAT);

    mesh_drawable one;
    one.initialize(number_mesh(1), "One");
    one.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - M_PI / 6);
    one.texture = number_texture;
    city_hierarchy.add(one, "Exterior", {115 * std::cos(M_PI / 6), - 115 * std::sin(M_PI / 6), 2});

    mesh_drawable two;
    two.initialize(number_mesh(2), "Two");
    two.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 2*M_PI / 6);
    two.texture = number_texture;
    city_hierarchy.add(two, "Exterior", {115 * std::cos(2 * M_PI / 6), - 115 * std::sin(2 * M_PI / 6), 2});

    mesh_drawable three;
    three.initialize(number_mesh(3), "Three");
    three.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 3*M_PI / 6);
    three.texture = number_texture;
    city_hierarchy.add(three, "Exterior", {115 * std::cos(3 * M_PI / 6), - 115 * std::sin(3 * M_PI / 6), 2});

    mesh_drawable four;
    four.initialize(number_mesh(4), "Four");
    four.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 4*M_PI / 6);
    four.texture = number_texture;
    city_hierarchy.add(four, "Exterior", {115 * std::cos(4 * M_PI / 6), - 115 * std::sin(4 * M_PI / 6), 2});

    mesh_drawable five;
    five.initialize(number_mesh(5), "Five");
    five.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 5*M_PI / 6);
    five.texture = number_texture;
    city_hierarchy.add(five, "Exterior", {115 * std::cos(5 * M_PI / 6), - 115 * std::sin(5 * M_PI / 6), 2});

    mesh_drawable six;
    six.initialize(number_mesh(6), "Six");
    six.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 6*M_PI / 6);
    six.texture = number_texture;
    city_hierarchy.add(six, "Exterior", {115 * std::cos(6 * M_PI / 6), - 115 * std::sin(6 * M_PI / 6), 2});

    mesh_drawable seven;
    seven.initialize(number_mesh(7), "Seven");
    seven.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 7*M_PI / 6);
    seven.texture = number_texture;
    city_hierarchy.add(seven, "Exterior", {115 * std::cos(7 * M_PI / 6), - 115 * std::sin(7 * M_PI / 6), 2});

    mesh_drawable eight;
    eight.initialize(number_mesh(8), "Eight");
    eight.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 8*M_PI / 6);
    eight.texture = number_texture;
    city_hierarchy.add(eight, "Exterior", {115 * std::cos(8 * M_PI / 6), - 115 * std::sin(8 * M_PI / 6), 2});

    mesh_drawable nine;
    nine.initialize(number_mesh(9), "Nine");
    nine.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 9*M_PI / 6);
    nine.texture = number_texture;
    city_hierarchy.add(nine, "Exterior", {115 * std::cos(9 * M_PI / 6), - 115 * std::sin(9 * M_PI / 6), 2});

    mesh_drawable ten;
    ten.initialize(number_mesh(10), "Ten");
    ten.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 10*M_PI / 6);
    ten.texture = number_texture;
    city_hierarchy.add(ten, "Exterior", {115 * std::cos(10 * M_PI / 6), - 115 * std::sin(10 * M_PI / 6), 2});

    mesh_drawable eleven;
    eleven.initialize(number_mesh(11), "Eleven");
    eleven.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 11*M_PI / 6);
    eleven.texture = number_texture;
    city_hierarchy.add(eleven, "Exterior", {115 * std::cos(11 * M_PI / 6), - 115 * std::sin(11 * M_PI / 6), 2});

    mesh_drawable twelve;
    twelve.initialize(number_mesh(12), "Twelve");
    twelve.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, - 12*M_PI / 6);
    twelve.texture = number_texture;
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

cgp::mesh number_mesh(int nb) {
    mesh num;
    if (nb == 1){
        num.push_back(brick(20, 2, 2));
        num.color.fill({1,0,0.5});
    }
    if (nb == 2) {
        num.push_back(brick(20, 2, 2, {0, -2, 0}));
        num.push_back(brick(20, 2, 2, {0, 2, 0}));
        num.color.fill({1,0,0});
    }
    if (nb == 3) {
        num.push_back(brick(20, 2, 2));
        num.push_back(brick(20, 2, 2, {0, -4, 0}));
        num.push_back(brick(20, 2, 2, {0, 4, 0}));
        num.color.fill({1,0.5,0});
    }
    if (nb == 4) {
        num.push_back(brick(20, 2, 2, {0, 7, 0}));
        num.push_back(v(20, 2, 2, {0, -2, 0}));
        num.color.fill({1,1,0});
    }
    if (nb == 5) {
        num.push_back(v(20, 2, 2));
        num.color.fill({0.5,1,0});
    }
    if (nb == 6) {
        num.push_back(brick(20, 2, 2, {0, -7, 0}));
        num.push_back(v(20, 2, 2, {0, 2, 0}));
        num.color.fill({0,1,0});
    }
    if (nb == 7) {
        num.push_back(brick(20, 2, 2, {0, -9, 0}));
        num.push_back(brick(20, 2, 2, {0, -5, 0}));
        num.push_back(v(20, 2, 2, {0, 4, 0}));
        num.color.fill({0,1,0.5});
    }
    if (nb == 8) {
        num.push_back(brick(20, 2, 2, {0, -11, 0}));
        num.push_back(brick(20, 2, 2, {0, -7, 0}));
        num.push_back(brick(20, 2, 2, {0, -3, 0}));
        num.push_back(v(20, 2, 2, {0, 6, 0}));
        num.color.fill({0,1,1});
    }
    if (nb == 9) {
        num.push_back(brick(20, 2, 2, {0, 7, 0}));
        num.push_back(x(20, 2, 2, {0, -2, 0}));
        num.color.fill({0,0.5,1});
    }
    if (nb == 10) {
        num.push_back(x(20, 2, 2));
        num.color.fill({0,0,1});
    }
    if (nb == 11) {
        num.push_back(brick(20, 2, 2, {0, -7, 0}));
        num.push_back(x(20, 2, 2, {0, 2, 0}));
        num.color.fill({0.5,0,1});
    }
    if (nb == 12) {
        num.push_back(brick(20, 2, 2, {0, -9, 0}));
        num.push_back(brick(20, 2, 2, {0, -5, 0}));
        num.push_back(x(20, 2, 2, {0, 4, 0}));
        num.color.fill({1,0,1});
    }
    num.color.fill({1,1,1});
    for (int i=0; i < num.uv.size(); i++) {
        num.uv[i] = (num.position[i].xy()+ vec2(0, num.position[i].z)) / 20;
    }
    return num;
}

// Buildings of dimensions l x w with streets of width s
cgp::mesh create_city(float l, float w, float s, int nl, int nw, float hmax)
{
    mesh city;
    for (int i=0; i<nl; i++) {
        for (int j=0; j<nw; j++) {
            float local_max_height = (1 - (float) i / (float) nl) * (1 - (float) i / (float) nl) * hmax;
            float h = rand_interval(local_max_height * 0.25, local_max_height);
            mesh block;
            //south face
            block.push_back(mesh_primitive_quadrangle({i*(l+s), j*(w+s), 0},
                                                    {i*(l+s) + l, j*(w+s), 0},
                                                    {i*(l+s) + l, j*(w+s), h},
                                                    {i*(l+s), j*(w+s), h}));
            
            //west face
            block.push_back(mesh_primitive_quadrangle({i*(l+s), j*(w+s) + w, 0},
                                                    {i*(l+s), j*(w+s), 0},
                                                    {i*(l+s), j*(w+s), h},
                                                    {i*(l+s), j*(w+s) + w, h}));
            
            //north face
            block.push_back(mesh_primitive_quadrangle({i*(l+s) + l, j*(w+s) + w, 0},
                                                    {i*(l+s), j*(w+s) + w, 0},
                                                    {i*(l+s), j*(w+s) + w, h},
                                                    {i*(l+s) + l, j*(w+s) + w, h}));
            
            //east face
            block.push_back(mesh_primitive_quadrangle({i*(l+s) + l, j*(w+s), 0},
                                                    {i*(l+s) + l, j*(w+s) + w, 0},
                                                    {i*(l+s) + l, j*(w+s) + w, h},
                                                    {i*(l+s) + l, j*(w+s), h}));
            
            //top face
            block.push_back(mesh_primitive_quadrangle({i*(l+s), j*(w+s), h},
                                                    {i*(l+s) + l, j*(w+s), h},
                                                    {i*(l+s) + l, j*(w+s) + w, h},
                                                    {i*(l+s), j*(w+s) + w, h}));
            block.color.fill(vec3(rand_interval(), rand_interval(), rand_interval()));
            city.push_back(block);
        }
    }
    city.fill_empty_field();
    return city;
}

float angle_increment(float t)
{
    float x = floorf(t);
    if (t-x < 0.75) return M_PI * x /6;
    else return M_PI * (x + 4 * (t-x-0.75)) / 6;
}