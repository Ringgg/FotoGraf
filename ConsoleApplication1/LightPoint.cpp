#include "stdafx.h"
#include "LightPoint.h"


LightPoint::LightPoint() { }
LightPoint::LightPoint(const LightPoint & light) : position(light.position), Light(light) { }
LightPoint::LightPoint(Float3 position, Color color) : position(position), Light(color) { }


void LightPoint::TestColor(Ray & ray, HitInfo & hit, vector<Shape*>& shapes,
	PhongColor& color)
{
	static Float3 fromMe2Pt;

	if (IsInShadow(hit.p - ray.direction * 1E-5, shapes))
	{
		color.diffuse *= 0;
		color.specular *= 0;
	}

	// shading
	fromMe2Pt = (hit.p - position).Normalized();
	Phong(fromMe2Pt, -ray.direction, hit.n, color.diffuse, color.specular, hit.objHit->material);
}

bool LightPoint::IsInShadow(Float3 pt, vector<Shape*>& shapes)
{
	static HitInfo nothing;
	static Float3 fromPt2Me;
	static Ray r;

	fromPt2Me = pt - position;
	Ray r(position, fromPt2Me, fromPt2Me.Length() - 1E-6);
	return Linear::Raycast(r, shapes, nothing);
}
