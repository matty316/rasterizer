#include "common.h"

int main() {
    InitWindow(screen_width, screen_height, "rasterizer");

    SetTargetFPS(60);

    model cube;
    cube.type = CUBE;
    instance instance1;
    instance1.model = &cube;
    instance1.position = { -1.5, 0, 7 };
    instance instance2;
    instance2.model = &cube;
    instance2.position = { 1.25, 2, 7.5 };

    scene scene;
    scene.instances.push_back(instance1);
    scene.instances.push_back(instance2);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        render_scene(scene);
        
        EndDrawing();
    }
    CloseWindow();
}
