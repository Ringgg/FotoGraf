#pragma once

class Linear
{
public:
	static float Distance(Float3 a, Float3 b);
	static float DistanceSquared(Float3 a, Float3 b);
	static float Dot(Float3 a, Float3 b);
	static float Angle(Float3 a, Float3 b);
	static float Abs(float val);
	static float ScalarTriple(Float3 u, Float3 v, Float3 w);

	static Float3 Cross(Float3 va, Float3 b);
	static Float3 Reflect(Float3 v, Float3 normal);
	static Float3 Lerp(Float3 a, Float3 b, float t);
	static Float3 Project(Float3 v, Float3 ontoV);

	static Float3 ClosestPtPointPlane(Float3 q, Plane p);
	static Float3 ClosestPtPointTriangle(Float3 p, Float3 a, Float3 b, Float3 c);
	static Float3 ClosesetPtPointSegment(Float3 c, Float3 a, Float3 b);

	static bool Intersects(Ray& r, Sphere& s, HitInfo& info);
	static bool Intersects(Ray& r, Plane& p, HitInfo& info);
	static bool Intersects(Ray& r, Triangle& t, HitInfo& info);

private:
	Linear();
	~Linear();
};