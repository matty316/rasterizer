#pragma once

void put_pixel(int x, int y, Color color) {
	x = screen_width / 2 + x;
	y = screen_height / 2 - y;
	DrawPixel(x, y, color);
}

void swap(Vector2& p0, Vector2& p1) {
    auto temp = p0;
    p0 = p1;
    p1 = temp;
}


void swap(Vector3& p0, Vector3& p1) {
    auto temp = p0;
    p0 = p1;
    p1 = temp;
}

std::vector<float> interpolate(int i0, float d0, int i1, float d1) {
	if (i0 == i1)
		return { d0 };
	

	std::vector<float> values;

	auto a = (d1 - d0) / (i1 - i0);
	auto d = d0;

	for (int i = i0; i <= i1; ++i) {
		values.push_back(d);
		d = d + a;
	}
	return values;
}

void draw_line(Vector2 p0, Vector2 p1, Color color) {
	if (std::abs(p1.x - p0.x) > std::abs(p1.y - p0.y)) {
		if (p0.x > p1.x)
            swap(p0, p1);
		
		auto ys = interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int x = p0.x; x <= p1.x; ++x) {
			put_pixel(x, ys[x - p0.x], color);
		}
	}
	else {
		if (p0.y > p1.y)
            swap(p0, p1);
		
		auto xs = interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int y = p0.y; y <= p1.y; ++y) {
			put_pixel(xs[y - p0.y], y, color);
		}
	}
}

void draw_wireframe_triangle(Vector2 p0, Vector2 p1, Vector2 p2, Color color) {
	draw_line(p0, p1, color);
	draw_line(p1, p2, color);
	draw_line(p2, p0, color);
}

void draw_filled_triangle(Vector2 p0, Vector2 p1, Vector2 p2, Color color) {
    if (p1.y < p0.y)
        swap(p1, p0);
    if (p2.y < p0.y)
        swap(p2, p0);
    if (p2.y < p1.y)
        swap(p2, p1);
    
    auto x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
    auto x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
    auto x02 = interpolate(p0.y, p0.x, p2.y, p2.x);
    
    x01.pop_back();
    std::vector<float> x012;
    for (auto &i : x01) {
        x012.push_back(i);
    }
    for (auto &i : x12) {
        x012.push_back(i);
    }
    
    auto m = size_t(x012.size() / 2);
    std::vector<float> x_left;
    std::vector<float> x_right;
    if (x02[m] < x012[m]) {
        x_left = x02;
        x_right = x012;
    } else {
        x_left = x012;
        x_right = x02;
    }
    
    for (int y = p0.y; y <= p2.y; ++y) {
        for (int x = x_left[y - p0.y]; x <= x_right[y - p0.y]; ++x) {
            put_pixel(x, y, color);
        }
    }
}

Color get_shaded_color(Color color, float h) {
    auto r = color.r * h;
    auto g = color.g * h;
    auto b = color.b * h;
    return { static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), color.a};
}

void draw_shaded_triangle(Vector3 p0, Vector3 p1, Vector3 p2, Color color) {
    if (p1.y < p0.y)
        swap(p1, p0);
    if (p2.y < p0.y)
        swap(p2, p0);
    if (p2.y < p1.y)
        swap(p2, p1);

    float h0 = p0.z;
    float h1 = p1.z;
    float h2 = p2.z;
    
    auto x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
    auto h01 = interpolate(p0.y, h0, p1.y, h1);

    auto x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
    auto h12 = interpolate(p1.y, h1, p2.y, h2);

    auto x02 = interpolate(p0.y, p0.x, p2.y, p2.x);
    auto h02 = interpolate(p0.y, h0, p2.y, h2);

    x01.pop_back();
    std::vector<float> x012;
    for (auto& i : x01) {
        x012.push_back(i);
    }
    for (auto& i : x12) {
        x012.push_back(i);
    }

    h01.pop_back();
    std::vector<float> h012;
    for (auto& i :h01) {
        h012.push_back(i);
    }
    for (auto& i : h12) {
        h012.push_back(i);
    }

    auto m = size_t(x012.size() / 2);
    std::vector<float> x_left;
    std::vector<float> x_right;
    std::vector<float> h_left;
    std::vector<float> h_right;
    if (x02[m] < x012[m]) {
        x_left = x02;
        h_left = h02;

        x_right = x012;
        h_right = h012;
    }
    else {
        x_left = x012;
        h_left = h012;

        x_right = x02;
        h_right = h02;
    }

    for (int y = p0.y; y <= p2.y; ++y) {
        auto x_l = x_left[y - p0.y];
        auto x_r = x_right[y - p0.y];

        auto h_segment = interpolate(x_l, h_left[y - p0.y], x_r, h_right[y - p0.y]);
        for (int x = x_l; x <= x_r; ++x) {
            auto shaded_color = get_shaded_color(color, h_segment[x - x_l]);
            put_pixel(x, y, shaded_color);
        }
    }
}

void render_triangle(triangle triangle, std::vector<Vector2> projected) {
    draw_wireframe_triangle(projected[triangle.v0], 
        projected[triangle.v1], 
        projected[triangle.v2],
        triangle.color
    );
}

void  render_object(std::vector<Vector3> verticies, std::vector<triangle> triangles) {
    std::vector<Vector2> projected;

    for (size_t i = 0; i < verticies.size(); i++) {
        projected.push_back(project_vertex(verticies[i]));
    }
    for (size_t i = 0; i < triangles.size(); i++) {
        render_triangle(triangles[i], projected);
    }
}

void render_instance(instance instance) {
    std::vector<Vector2> projected;
    auto model = instance.model;
    for (auto& vertex : model->vertices) {
        auto v_prime = vertex + instance.position;
        projected.push_back(project_vertex(v_prime));
    }
    for (auto& triangle : model->triangles) {
        render_triangle(triangle, projected);
    }
}

void render_scene(scene& scene) {
    for (auto& instance : scene.instances) {
        render_instance(instance);
    }
}