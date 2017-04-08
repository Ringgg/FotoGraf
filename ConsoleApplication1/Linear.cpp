#include "stdafx.h"
#include "Linear.h"

Linear::Linear() { }
Linear::~Linear() { }

float Linear::Distance(Float3 a, Float3 b) { return (b - a).Length(); }
float Linear::DistanceSquared(Float3 a, Float3 b) { return (b - a).LengthSquared(); }
float Linear::Dot(Float3 a, Float3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
float Linear::Angle(Float3 a, Float3 b) { return -1; }
float Linear::Abs(float val) { return val > 0 ? val : - val; }
float Linear::ScalarTriple(Float3 u, Float3 v, Float3 w) { return Dot(Cross(u, v), w); }
Float3 Linear::Cross(Float3 a, Float3 b) { return Float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
Float3 Linear::Reflect(Float3 v, Float3 normal) { return v - normal * Dot(v, normal) * 2; }
Float3 Linear::Lerp(Float3 a, Float3 b, float t) { return a*(1 - t) + b*t; }
Float3 Linear::Project(Float3 v, Float3 ontoV) { return ontoV * Dot(v, ontoV); }
Float3 Linear::ClosestPtPointPlane(Float3 q, Plane p) { return q - p.normal * (Dot(p.normal, q) - p.distance); }

Float3 Linear::ClosestPtPointTriangle(Float3 p, Float3 a, Float3 b, Float3 c)
{
	// Check if P in vertex region outside A
	Float3 ab = b - a;
	Float3 ac = c - a;
	Float3 ap = p - a;
	float d1 = Dot(ab, ap);
	float d2 = Dot(ac, ap);
	float v;
	float w;
	if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)
											// Check if P in vertex region outside B
	Float3 bp = p - b;
	float d3 = Dot(ab, bp);
	float d4 = Dot(ac, bp);
	if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)
										  // Check if P in edge region of AB, if so return projection of P onto AB
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		v = d1 / (d1 - d3);
		return a + ab * v; // barycentric coordinates (1-v,v,0)
	}
	// Check if P in vertex region outside C
	Float3 cp = p - c;
	float d5 = Dot(ab, cp);
	float d6 = Dot(ac, cp);
	if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)
										  // Check if P in edge region of AC, if so return projection of P onto AC
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		w = d2 / (d2 - d6);
		return a + ac * w; // barycentric coordinates (1-w,0,w)
	}
	// Check if P in edge region of BC, if so return projection of P onto BC
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return b + (c - b) * w; // barycentric coordinates (0,1-w,w)
	}
	// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
	float denom = 1.0f / (va + vb + vc);
	v = vb * denom;
	w = vc * denom;
	return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f-v-w
}

Float3 Linear::ClosesetPtPointSegment(Float3 c, Float3 a, Float3 b)
{
	Float3 d;
	Float3 ab = b - a;
	float t = Dot(c - a, ab) / Dot(ab, ab);

	if (t < 0.0f) t = 0.0f;
	else if (t > 1.0f) t = 1.0f;
	d = a + ab * t;
	return d;
}

bool Linear::Intersects(Ray& r, Sphere& s, HitInfo & info)
{
	static float t0, t1, tca, thc, d2;
	static Float3 L;

	L = s.pos - r.origin;
	tca = Dot(L, r.direction);
	d2 = Dot(L, L) - tca * tca;

	if (d2 > s.r * s.r) return false; // ray missed

	thc = sqrt(s.r * s.r - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) swap(t0, t1);
	if (t0 < 0)
	{
		if (t1 < 0) return false; // sphere behind ray
		t0 = t1;
	}

	if (t0 > r.distace) return false; // ray was too short;

	info.d = t0;
	info.p = r.origin + r.direction * t0;
	info.n = (s.pos - info.p).Normalized();	

	return true;
}

bool Linear::Intersects(Ray& r, Plane& p, HitInfo & info)
{
	static float denom;
	static Float3 p2r;

	denom = Dot(p.normal, r.direction);
	if (denom > 1e-6) return false; // ray pararell to plane or opposite
	
	p2r = p.normal * p.distance - r.origin;
	info.d = Dot(p2r, p.normal) / denom;
	info.p = r.origin + r.direction * info.d;
	info.n = p.normal;

	return info.d >= 0 && info.d <= r.distace; // other cases
}

bool Linear::Intersects(Ray& r, Triangle& t, HitInfo& info)
{
	static float denom;
	static Float3 fx, fy, fz;

	denom = Dot(t.n, r.direction);
	if (denom > 1e-6F) return false;					 // ray pararell to plane or opposite

	info.d = Dot(t.n * t.d - r.origin, t.n) / denom;
	if (info.d > r.distace) return false;				 // ray is too short

	info.p = r.origin + r.direction * info.d;
	fx = t.x - info.p; fy = t.y - info.p; fz = t.z - info.p;
	if(Dot(Cross(fx, fy), t.n)< -0.00001F) return false; // triangle missed
	if(Dot(Cross(fy, fz), t.n)< -0.00001F) return false; // triangle missed
	if(Dot(Cross(fz, fx), t.n)< -0.00001F) return false; // triangle missed
	info.n = t.n;
	return true;
};