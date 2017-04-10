#pragma once

struct Shape
{
	Shape();
	Shape(Float3 position);

	virtual bool IntersectsWith(Ray& ray, HitInfo& info) = 0;

	Float3 pos;
	Material* material;
};