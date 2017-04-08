#pragma once
struct Plane
{
	Float3 normal;
	float distance;

	~Plane();
	Plane(Float3 norm = Float3(0,1,0), float dist = 0);
};

