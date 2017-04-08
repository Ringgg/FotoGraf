#pragma once
struct Sphere : public Shape
{
	float r;

	~Sphere();
	Sphere();
	Sphere(Float3 position, float radius);

	bool IntersectsWith(Ray& ray, HitInfo& info);
};


inline std::ostream& operator<<(std::ostream& os, Sphere a)
{
	os << "Sphere(center:" << a.pos << ", radius: " << a.r << ")"; 
	return os; 
}

