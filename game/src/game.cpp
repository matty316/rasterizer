#include "common.h"

void main() { 
    InitWindow(screen_width, screen_height, "rasterizer");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        Vector2 p0(-200, -250);
        Vector2 p1(200, 50);
        Vector2 p2(20, 250);
        draw_wireframe_triangle(p0, p1, p2, BLACK);
        EndDrawing();
    }
    CloseWindow();
}