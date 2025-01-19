#pragma once

struct triangle {
	float v0;
	float v1;
	float v2;
	Color color;
};

enum model_type {
    CUBE
};

struct model {
    model_type type = CUBE;
    std::vector<Vector3> vertices{
        {1, 1, 1},
        { -1, 1, 1 },
        { -1, -1, 1 },
        { 1, -1, 1 },
        { 1, 1, -1 },
        { -1, 1, -1 },
        { -1, -1, -1 },
        { 1, -1, -1 },
    };
    std::vector<triangle> triangles{
         { 0, 1, 2, RED},
         { 0, 2, 3, RED},
         { 4, 0, 3, GREEN},
         { 4, 3, 7, GREEN},
         { 5, 4, 7, BLUE},
         { 5, 7, 6, BLUE},
         { 1, 5, 6, YELLOW},
         { 1, 6, 2, YELLOW},
         { 4, 5, 1, PURPLE},
         { 4, 1, 0, PURPLE},
         { 2, 6, 7, SKYBLUE},
         { 2, 7, 3, SKYBLUE}
    };
};

struct instance {
    model *model;
    Vector3 position;
};

struct scene {
    std::vector<instance> instances;
};