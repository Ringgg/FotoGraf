#pragma once
struct Plane : public Shape
{
	Float3 normal;
	double distance;

	~Plane();
	Plane(Float3 norm = Float3(0,1,0), double dist = 0);

	bool IntersectsWith(Ray& ray, HitInfo& info);
};

