#pragma once

void put_pixel(int x, int y, Color color) {
	x = screen_width / 2 + x;
	y = screen_height / 2 - y;
	DrawPixel(x, y, color);
}

std::vector<int> interpolate(int i0, float d0, int i1, float d1) {
	if (i0 == i1) {
		return { int(d0) };
	}

	std::vector<int> values;

	auto a = (d1 - d0) / (i1 - i0);
	auto d = d0;

	for (int i = i0; i <= i1; ++i) {
		values.push_back(int(d));
		d = d + a;
	}
	return values;
}

void draw_line(Vector2 p0, Vector2 p1, Color color) {
	if (std::abs(p1.x - p0.x) > std::abs(p1.y - p0.y)) {
		if (p0.x > p1.x) {
			auto temp = p0;
			p0 = p1;
			p1 = temp;
		}
		auto ys = interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int x = p0.x; x <= p1.x; ++x) {
			put_pixel(x, ys[x - p0.x], color);
		}
	}
	else {
		if (p0.y > p1.y) {
			auto temp = p0;
			p0 = p1;
			p1 = temp;
		}
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