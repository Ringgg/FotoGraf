#include "stdafx.h"
#include "Plane.h"


Plane::~Plane() { }
Plane::Plane(Float3 norm, double dist): normal(norm), distance(dist)
{
	normal.Normalize();
}

bool Plane::IntersectsWith(Ray & ray, HitInfo & info)
{
	static double denom;
	static Float3 p2r;

	denom = Linear::Dot(normal, ray.direction);
	if (denom > 1e-6) return false; // ray pararell to plane or opposite

	p2r = normal * distance - ray.origin;
	info.d = Linear::Dot(p2r, normal) / denom;
	info.p = ray.origin + ray.direction * info.d;
	info.n = normal;
	info.objHit = this;

	return info.d >= 0 && info.d <= ray.distace; // other cases
}
