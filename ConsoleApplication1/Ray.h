#pragma once
struct Ray
{
	Float3 origin, direction;
	float distace;

	~Ray();
	Ray();
	Ray(Float3 orig, Float3 dir, float dist = 1000000);
};

inline std::ostream& operator<<(std::ostream& os, Ray a) { os << "Ray(origin:" << a.origin << ", direction: " << a.direction << ")";  return os; }