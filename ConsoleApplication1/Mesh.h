#pragma once
struct Mesh : Shape
{
	string name;

	vector<Triangle> tris;

	Mesh();
	Mesh(vector<Triangle> &tris);

	bool IntersectsWith(Ray& ray, HitInfo& info);
};

