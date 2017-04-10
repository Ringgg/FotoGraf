#include "stdafx.h"
#include "Linear.h"

Linear::Linear() { }
Linear::~Linear() { }

Float3 Linear::ClosestPtPointPlane(Float3 q, Plane p) { return q - p.normal * (Dot(p.normal, q) - p.distance); }

Float3 Linear::ClosestPtPointTriangle(Float3 p, Float3 a, Float3 b, Float3 c)
{
	// Check if P in vertex region outside A
	Float3 ab = b - a;
	Float3 ac = c - a;
	Float3 ap = p - a;
	double d1 = Dot(ab, ap);
	double d2 = Dot(ac, ap);
	double v;
	double w;
	if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)
											// Check if P in vertex region outside B
	Float3 bp = p - b;
	double d3 = Dot(ab, bp);
	double d4 = Dot(ac, bp);
	if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)
										  // Check if P in edge region of AB, if so return projection of P onto AB
	double vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		v = d1 / (d1 - d3);
		return a + ab * v; // barycentric coordinates (1-v,v,0)
	}
	// Check if P in vertex region outside C
	Float3 cp = p - c;
	double d5 = Dot(ab, cp);
	double d6 = Dot(ac, cp);
	if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)
										  // Check if P in edge region of AC, if so return projection of P onto AC
	double vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		w = d2 / (d2 - d6);
		return a + ac * w; // barycentric coordinates (1-w,0,w)
	}
	// Check if P in edge region of BC, if so return projection of P onto BC
	double va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return b + (c - b) * w; // barycentric coordinates (0,1-w,w)
	}
	// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
	double denom = 1.0f / (va + vb + vc);
	v = vb * denom;
	w = vc * denom;
	return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f-v-w
}

Float3 Linear::ClosesetPtPointSegment(Float3 c, Float3 a, Float3 b)
{
	Float3 d;
	Float3 ab = b - a;
	double t = Dot(c - a, ab) / Dot(ab, ab);

	if (t < 0.0f) t = 0.0f;
	else if (t > 1.0f) t = 1.0f;
	d = a + ab * t;
	return d;
}

bool Linear::Intersects(Ray& r, Sphere& s, HitInfo & info)
{
	static double t0, t1, tca, thc, d2;
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
	static double denom;
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
	static float  invArea, denom;
	Float3 N;

	denom = Dot(t.n, r.direction);
	if (denom > -1e-6) return false; // ray parallel
	info.d = Dot(t.n * Dot(t.x, t.n) - r.origin, t.n) / denom;
	if (info.d < 0 || info.d > r.distace) return false; // ray behind or too short
	info.p = r.origin + r.direction * info.d;

	N = Cross(t.y - t.x, t.z - t.x);
	if ((Dot(N, Cross(t.y - t.x, info.p - t.x))) < 0) return false; // miss
	if ((info.uvw.x = Dot(N, Cross(t.z - t.y, info.p - t.y))) < 0)  return false; // miss 
	if ((info.uvw.y = Dot(N, Cross(t.x - t.z, info.p - t.z))) < 0) return false; // miss
	
	invArea = 1.0 / Dot(N, N); 
	info.uvw.x *= invArea;
	info.uvw.y *= invArea;
	info.uvw.z  = 1 - info.uvw.x - info.uvw.y;
	info.n = t.n;

	return true; // ray hits triangle
}



bool Linear::Raycast(Ray & r, vector<Shape*>& shapes, HitInfo & info)
{
	static HitInfo cur;
	info = HitInfo(Float3(), Float3());
	for (int i = 0; i < shapes.size(); ++i)
		if (shapes[i]->IntersectsWith(r, cur))
			if (cur.d < info.d)
				info = cur;
	return info.d < r.distace;
}

//bool Linear::Intersects(Ray& r, Triangle& t, HitInfo& info)
//{
//	static double denom;
//	static Float3 fx, fy, fz;
//
//	denom = Dot(t.n, r.direction);
//	if (denom > 1e-6F) return false;					 // ray pararell to plane, opposite, or wrong side
//
//	info.d = Dot(t.n * Dot(t.x, t.n) - r.origin, t.n) / denom;
//	if (info.d > r.distace) return false;				 // ray is too short
//
//	info.p = r.origin + r.direction * info.d;
//	fx = t.x - info.p; fy = t.y - info.p; fz = t.z - info.p;
//	if (Dot(Cross(fx, fy), t.n)< -1e-6F) return false; // triangle missed
//	if (Dot(Cross(fy, fz), t.n)< -1e-6F) return false; // triangle missed
//	if (Dot(Cross(fz, fx), t.n)< -1e-6F) return false; // triangle missed
//	info.n = t.n;
//	return true;
//}
