#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle() { }

Triangle::Triangle(Float3 x, Float3 y, Float3 z) : x(x), y(y), z(z)
{
	n = Linear::Cross(y - x, z - x).Normalized();
}

Triangle::Triangle(
	Float3 x, Float3 y, Float3 z,
	Float3 UVx, Float3 UVy, Float3 UVz)
	: x(x), y(y), z(z),
	UVx(UVx), UVy(UVy), UVz(UVz)
{
	n = Linear::Cross(y - x, z - x).Normalized();
}


Triangle::Triangle(const Triangle & other)
	: x(other.x), y(other.y), z(other.z), n(other.n),
	  UVx(other.UVx), UVy(other.UVy), UVz(other.UVz){ }
