#include "stdafx.h"
#include "Ray.h"


Ray::Ray() : origin(Float3()), direction(Float3(1,0,0)), distace(1000000) { }
Ray::Ray(Float3 orig, Float3 dir, float dist): origin(orig), direction(dir), distace(dist)
{
	static float sqlen;
	sqlen = dir.LengthSquared() - 1;
	if (sqlen * sqlen > 1e-6)
		direction.Normalize();
} 
Ray::~Ray() { }
