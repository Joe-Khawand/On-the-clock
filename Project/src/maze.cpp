#include "maze.hpp"

cgp::mesh initialize_maze(int nl, int nw, float c, float h) {
    int maze[nl * nw];

	for (int i=0; i<nl; i++) {
        for (int j=0; j<nw; j++) {
            maze[i * nw + j] = 1;
        }
    }

    std::vector<std::pair<int, int> > stack;
    maze[nw + 1] = 0;
    stack.push_back({1, 2});
    stack.push_back({2, 1});

    while (stack.size() > 0)
    {
        std::pair<int, int> p = stack[stack.size()-1];
        int i = p.first;
        int j = p.second;
        stack.pop_back();
        if (!(i==0 or i==nl-1 or j==0 or j==nw-1 or maze[i*nw +j]==0 
            or maze[i*nw +j-1] + maze[(i+1)*nw +j] + maze[i*nw +j+1] + maze[(i-1)*nw +j] < 3))
        {
			std::pair<int, int> next;
			if (maze[(i-1) * nw +j] == 0) next = {i+1, j};
			else {
				if (maze[(i+1) * nw +j] == 0) next = {i-1, j};
				else {
					if (maze[i * nw +j-1] == 0) next = {i, j+1};
					else {
						if (maze[i * nw +j+1] == 0) next = {i, j-1};
						else
							next = {-1, -1};
					}
				}
			}
			
            int i2 = next.first;
            int j2 = next.second;
            std::vector<std::pair<int, int> > li = neighboring_walls(i2, j2);
            for (std::pair<int, int> pair:li) {
                stack.push_back(pair);
            }
            maze[i2 * nw + j2] = 0;
            maze[i * nw + j] = 0;
        }
    }

    // generate maze mesh
    // **********************
    
    cgp::mesh maze_mesh;
    for (int i=0; i<nl-1; i++) {
        for (int j=0; j<nl-1; j++) {
            if (maze[i*nw + j] == 1){
                maze_mesh.push_back(cgp::mesh_primitive_quadrangle({i*c, j*c, h},
                                                                    {(i+1)*c, j*c, h},
                                                                    {(i+1)*c, (j+1)*c, h},
                                                                    {i*c, (j+1)*c, h}));
                if (maze[(i+1)*nw + j] == 0){
                    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(i+1)*c, j*c, h},
                                                                    {(i+1)*c, j*c, 0},
                                                                    {(i+1)*c, (j+1)*c, 0},
                                                                    {(i+1)*c, (j+1)*c, h}));
                }
                if (maze[i*nw + (j+1)] == 0){
                    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(i+1)*c, (j+1)*c, h},
                                                                    {(i+1)*c, (j+1)*c, 0},
                                                                    {i*c, (j+1)*c, 0},
                                                                    {i*c, (j+1)*c, h}));
                }
            }
            if (maze[i*nw + j] == 0){
                if (maze[(i+1)*nw + j] == 1){
                    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(i+1)*c, j*c, 0},
                                                                    {(i+1)*c, j*c, h},
                                                                    {(i+1)*c, (j+1)*c, h},
                                                                    {(i+1)*c, (j+1)*c, 0}));
                }
                if (maze[i*nw + (j+1)] == 1){
                    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(i+1)*c, (j+1)*c, 0},
                                                                    {(i+1)*c, (j+1)*c, h},
                                                                    {i*c, (j+1)*c, h},
                                                                    {i*c, (j+1)*c, 0}));
                }
            }
        }
    }
    for (int i=0; i<nl-1; i++) {
        maze_mesh.push_back(cgp::mesh_primitive_quadrangle({i*c, 0, h},
                                                            {i*c, 0, 0},
                                                            {(i+1)*c, 0, 0},
                                                            {(i+1)*c, 0, h}));
        maze_mesh.push_back(cgp::mesh_primitive_quadrangle({i*c, nw*c, 0},
                                                            {i*c, nw*c, h},
                                                            {(i+1)*c, nw*c, h},
                                                            {(i+1)*c, nw*c, 0}));
        maze_mesh.push_back(cgp::mesh_primitive_quadrangle({i*c, nw*c, h},
                                                            {i*c, (nw-1)*c, h},
                                                            {(i+1)*c, (nw-1)*c, h},
                                                            {(i+1)*c, nw*c, h}));
    }
    for (int j=0; j<nw-1; j++) {
        maze_mesh.push_back(cgp::mesh_primitive_quadrangle({nl*c, j*c, h},
                                                            {nl*c, j*c, 0},
                                                            {nl*c, (j+1)*c, 0},
                                                            {nl*c, (j+1)*c, h}));
        maze_mesh.push_back(cgp::mesh_primitive_quadrangle({0, j*c, 0},
                                                            {0, j*c, h},
                                                            {0, (j+1)*c, h},
                                                            {0, (j+1)*c, 0}));
        maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(nl-1)*c, (j+1)*c, h},
                                                            {(nl-1)*c, j*c, h},
                                                            {nl*c, j*c, h},
                                                            {nl*c, (j+1)*c, h}));
    }
    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(nl-1)*c, 0, h},
                                                            {(nl-1)*c, 0, 0},
                                                            {nl*c, 0, 0},
                                                            {nl*c, 0, h}));
    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({0, (nw-1)*c, 0},
                                                            {0, (nw-1)*c, h},
                                                            {0, nw*c, h},
                                                            {0, nw*c, 0}));
    // top right corner
    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(nl-1)*c, nw*c, h},
                                                            {(nl-1)*c, (nw-1)*c, h},
                                                            {nl*c, (nw-1)*c, h},
                                                            {nl*c, nw*c, h}));
    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({(nl-1)*c, nw*c, 0},
                                                            {(nl-1)*c, nw*c, h},
                                                            {nl*c, nw*c, h},
                                                            {nl*c, nw*c, 0}));
    maze_mesh.push_back(cgp::mesh_primitive_quadrangle({nl*c, (nw-1)*c, h},
                                                            {nl*c, (nw-1)*c, 0},
                                                            {nl*c, nw*c, 0},
                                                            {nl*c, nw*c, h}));
    return maze_mesh;
}

void initialize_wrap_maze(int nl, int nw) {
    // generate maze matrix
    int maze[nl * (nw-1)];

	for (int i=0; i<nl; i++) {
        for (int j=0; j<nw-1; j++) {
            maze[i * nw + j] = 1;
        }
    }

    std::vector<std::pair<int, int> > stack;
    maze[nw + 1] = 0;
    stack.push_back({1, 2});
    stack.push_back({2, 1});

    while (stack.size() > 0)
    {
        std::pair<int, int> p = stack[stack.size()-1];
        int i = p.first;
        int j = p.second % (nw-1);
        stack.pop_back();
        if (!(i==0 or i==nl-1 or maze[i*nw +j]==0 
            or maze[i*nw + ((j-1)%(nw-1))] + maze[(i+1)*nw +j] + maze[i*nw +((j+1)%(nw-1))] + maze[(i-1)*nw +j] < 3))
        {
			std::pair<int, int> next;
			if (maze[(i-1) * nw +j] == 0) next = {i+1, j};
			else {
				if (maze[(i+1) * nw +j] == 0) next = {i-1, j};
				else {
					if (maze[i * nw +((j-1)%(nw-1))] == 0) next = {i, j+1};
					else {
						if (maze[i * nw +((j+1)%(nw-1))] == 0) next = {i, j-1};
						else
							next = {-1, -1}; // generates an error but shouldn't happen
					}
				}
			}
			
            int i2 = next.first;
            int j2 = next.second;
            std::vector<std::pair<int, int> > li = neighboring_walls(i2, j2);
            for (std::pair<int, int> pair:li) {
                stack.push_back(pair);
            }
            maze[i2 * nw + (j2%(nw-1))] = 0;
            maze[i * nw + j] = 0;
        }
    }

    // generate maze mesh
    // **********************

    cgp::mesh maze_mesh;
}

std::vector<std::pair<int, int> > neighboring_walls(int i, int j){
    std::vector<std::pair<int, int> > t;
    t.push_back({i, j-1});
    t.push_back({i+1, j});
    t.push_back({i, j+1});
    t.push_back({i-1, j});

	int d[4];
    for (int i=0; i<4; i++) {
        d[i] = i;
    }
    for (int i=0; i<4-1; i++) {
        int j = i + (rand() % (4-i));
        int temp = d[i];
        d[i] = d[j];
        d[j] = temp;
    }
    std::vector<std::pair<int, int> > t2;
    for (int i=0; i<4; i++) {
        t2.push_back(t[d[i]]);
    }
    return t2;
}