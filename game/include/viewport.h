#pragma once

Vector2 viewport_to_canvas(float x, float y) {
    return { x * screen_width / viewport_width, y * screen_height / viewport_height };
}

Vector2 project_vertex(Vector3 vertex) {
    return viewport_to_canvas(vertex.x * projection_plane_z / vertex.z, vertex.y * projection_plane_z / vertex.z);
}