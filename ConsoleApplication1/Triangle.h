#pragma once

struct Triangle
{
	Float3 x, y, z, n, UVx, UVy, UVz;

	Triangle();
	Triangle(Float3 x, Float3 y, Float3 z);
	Triangle(Float3 x, Float3 y, Float3 z, Float3 UVx, Float3 UVy, Float3 UVz);
	Triangle(const Triangle& other);
};
