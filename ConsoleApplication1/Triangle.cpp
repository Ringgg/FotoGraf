#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle() { }

Triangle::Triangle(Float3 x, Float3 y, Float3 z) : x(x), y(y), z(z)
{
	n = Linear::Cross(y - x, z - x).Normalized();
	d = Linear::Dot(x, n);
}

Triangle::Triangle(const Triangle & other) : x(other.x), y(other.y), z(other.z), d(other.d), n(other.n) { }
