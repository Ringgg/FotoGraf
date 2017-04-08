#pragma once
struct Mesh : Shape
{
	vector<Triangle> tris;

	Mesh();
	Mesh(vector<Triangle> &tris);

	bool IntersectsWith(Ray& ray, HitInfo& info);
};

