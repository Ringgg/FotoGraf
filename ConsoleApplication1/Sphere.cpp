#include "stdafx.h"
#include "Sphere.h"

Sphere::~Sphere() { }
Sphere::Sphere() { }
Sphere::Sphere(Float3 position, double radius) : Shape(position), r(radius) { }

bool Sphere::IntersectsWith(Ray& ray, HitInfo & info)
{
	static double t0, t1, tca, thc, d2;
	static Float3 L;

	L = pos - ray.origin;

	if (L.LengthSquared() < r * r) return false; //ray inside sphere

	tca = Linear::Dot(L, ray.direction);
	d2 = Linear::Dot(L, L) - tca * tca;

	if (d2 > r * r) return false; // ray missed

	thc = sqrt(r * r - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) swap(t0, t1);
	if (t0 < 0)
	{
		if (t1 < 0) return false; // sphere behind ray
		t0 = t1;
	}

	if (t0 > ray.distace) return false; // ray was too short;

	info.d = t0;
	info.p = ray.origin + ray.direction * t0;
	info.n = (info.p - pos).Normalized();
	info.objHit = this;
	info.triHit = 0;

	return true;
}
