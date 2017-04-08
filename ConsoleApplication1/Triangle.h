#pragma once

struct Triangle
{
	float d;
	Float3 x, y, z, n;

	Triangle();
	Triangle(Float3 x, Float3 y, Float3 z);
	Triangle(const Triangle& other);
};
