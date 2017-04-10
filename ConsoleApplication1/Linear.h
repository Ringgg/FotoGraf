#pragma once

class Linear
{
public:
	inline static double Distance(Float3 a, Float3 b) { return (b - a).Length(); }
	inline static double DistanceSquared(Float3 a, Float3 b) { return (b - a).LengthSquared(); }
	inline static double Dot(Float3& a, Float3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	inline static double Angle(Float3 a, Float3 b) { return -1; }
	inline static double Abs(double val) { return val > 0 ? val : -val; }
	inline static double ScalarTriple(Float3 u, Float3 v, Float3 w) { return Dot(Cross(u, v), w); }

	inline static Float3 Cross(Float3& a, Float3& b) { return Float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
	inline static Float3 Reflect(Float3 v, Float3 normal) { return v - normal * Dot(v, normal) * 2; }
	inline static Float3 Lerp(Float3 a, Float3 b, double t) { return a*(1 - t) + b*t; }
	inline static Float3 Project(Float3 v, Float3 ontoV) { return ontoV * Dot(v, ontoV); }

	static Float3 ClosestPtPointPlane(Float3 q, Plane p);
	static Float3 ClosestPtPointTriangle(Float3 p, Float3 a, Float3 b, Float3 c);
	static Float3 ClosesetPtPointSegment(Float3 c, Float3 a, Float3 b);

	static bool Intersects(Ray& r, Sphere& s, HitInfo& info);
	static bool Intersects(Ray& r, Plane& p, HitInfo& info);
	static bool Intersects(Ray& r, Triangle& t, HitInfo& info);

	static bool Raycast(Ray& r, vector<Shape*>& shapes, HitInfo& info);

private:
	Linear();
	~Linear();
};