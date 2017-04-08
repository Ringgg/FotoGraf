#include "stdafx.h"

void CollTest();
void ImgTest();
void RenderTestOrtho();
void RenderTestPersp();
void ObjTest();
void MeshRenderTest();

int main()
{
	//CollTest();
	//ImgTest();
	//RenderTestOrtho();
	//RenderTestPersp();
	//ObjTest();
	MeshRenderTest();
	//cout << "Enter any key: ";
	//getchar();
    return 0;
}

void CollTest()
{
	Ray r1(Float3(0, 0, -10), Float3(0, 0, 1));
	Ray r2(Float3(0, 0, -10), Float3(0, 1, 0));
	Ray r3(Float3(0, -10, -10), Float3(0, 0, 1));

	HitInfo info;
	Sphere s(Float3(), 10);
	Plane p(Float3(0, -1, -1), 0);

	if (Linear::Intersects(r1, s, info))
		cout << r1 << " collided with " << s << " at point: " << info.p << "\n";

	if (Linear::Intersects(r2, s, info))
		cout << r2 << " collided with " << s << " at point: " << info.p << "\n";

	if (Linear::Intersects(r3, s, info))
		cout << r3 << " collided with " << s << " at point: " << info.p << "\n";

	if (Linear::Intersects(r2, p, info))
		cout << r2 << " collided with plane at point: " << info.p << "\n";
}

void ImgTest()
{
	bitmap_image image;
	LightIntensity light;
	image.setwidth_height(100, 100, true);

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			light((double)i / 100, (double)j / 100);
			image.set_pixel(i, j, light);
		}
	}

	image.save_image("hoi.bmp");
}

void RenderTestOrtho()
{
	// camera = CameraOrtho(w, h, pxSize, pos, dir, u); 500,500,0.1, Float3(0,0,-12), Float3(0,0,1), Float3(0,1,0)
	Scene s;
	s.shapes.push_back(new Sphere(Float3(-2, -2, 4), 4));
	s.shapes.push_back(new Sphere(Float3(2, 2, 0), 4));
	s.camera = new CameraOrtho(500, 500, 0.05, Float3(0, 0, -12), Float3(0, 0, 1), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("hoii.bmp");
}

void RenderTestPersp()
{
	Scene s;
	s.shapes.push_back(new Sphere(Float3(-2, -2, 4), 4));
	s.shapes.push_back(new Sphere(Float3(2, 2, 0), 4));
	s.camera = new CameraPersp(1000, 1000, 60, 0.1, 1000, Float3(0, 0, -12), Float3(0, 0, 1), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("hoii7.bmp");
}

void ObjTest()
{
	ObjReader reader;
	Mesh m = reader.loadMesh("Cube.obj");
	cout << "done loading obj\n";
}

void MeshRenderTest()
{
	ObjReader reader;
	Mesh m = reader.loadMesh("Cube.obj");

	Scene s;
	s.shapes.push_back(&m);
	s.camera = new CameraPersp(500, 500, 60, 0.1, 1000, Float3(-1.5, 2.5, -1.5), Float3(0.5, -0.5, 0.5), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("hoiii.bmp");
}

/*
class Detection
{
// Tests collision between tho colliders and all of their descendants, if there are any
public static bool CollidesWith(Collider c1, Collider c2, List<Collision> colls)
{
	BoundingSphere S1 = c1.boundingSphere.Transform(c1.Actor.transform.Matrix);
	BoundingSphere S2 = c2.boundingSphere.Transform(c2.Actor.transform.Matrix);
	Collision coll = new Collision();

	if (Intersects(S1, S2, coll))
	{
		List<Collider> L1 = c1.GetDescendantColliders();
		List<Collider> L2 = c2.GetDescendantColliders();

		for (int i = 0; i < L1.Count; ++i)
		{
			for(int j = 0; j < L2. Count; ++j)
			{
				if (L1[i].isBounding || L2[j].isBounding)
					CollidesWith(L1[i], L2[j], colls);
				else
				{
					coll = new Collision();
					if (CollidesWith(L1[i], L2[j], coll))
					colls.Add(coll);
				}
			}
		}
	}

	return colls.Count > 0;
}

// tests collision between two colliders
public static bool CollidesWith(Collider c1, Collider c2, Collision collision)
{
	BoundingSphere S1 = c1.boundingSphere.Transform(c1.Actor.transform.Matrix);
	BoundingSphere S2 = c2.boundingSphere.Transform(c2.Actor.transform.Matrix);

	if (Intersects(S1, S2, collision))
	{
		collision.first = c1.Actor;
		collision.second = c2.Actor;

		collision.relativeVelocity = (c1.Actor.rigidbody != null) ? c1.Actor.rigidbody.velocity : Vector3.Zero;

		if (c2.Actor.rigidbody != null)
			collision.relativeVelocity += c2.Actor.rigidbody.velocity;

		if (!c1.box && !c2.box)
		{
			return true;
		}
		else if (c1.box && c2.box)
		{
			OrientedBoundingBox B1 = new OrientedBoundingBox(c1.boundingBox, c1.Actor.transform.Matrix);
			OrientedBoundingBox B2 = new OrientedBoundingBox(c2.boundingBox, c2.Actor.transform.Matrix);

			return B1.Intersects(B2);
		}
		else if (c1.box)
		{
			OrientedBoundingBox B1 = new OrientedBoundingBox(c1.boundingBox, c1.Actor.transform.Matrix);
			float sqDist = B1.Intersects(S2, out collision.point, out collision.normal);

			if (sqDist < c2.boundingSphere.Radius * c2.boundingSphere.Radius)
			{
				collision.normal *= -1.0f;
				collision.overlapping = c2.boundingSphere.Radius - (float)Math.Sqrt(sqDist);
				return true;
			}
		}
		else if (c2.box)
		{
			OrientedBoundingBox B2 = new OrientedBoundingBox(c2.boundingBox, c2.Actor.transform.Matrix);
			float sqDist = B2.Intersects(S1, out collision.point, out collision.normal);

			if (sqDist < c1.boundingSphere.Radius * c1.boundingSphere.Radius)
			{
				collision.overlapping = c1.boundingSphere.Radius -(float)Math.Sqrt(sqDist);
				return true;
			}
		}
	}
	return false;
}


public static bool Intersects(Actor a, BoundingFrustum b)
{
	if (a.GetComponent<ParticleSystem>() != null)
	if (b.Contains(new BoundingSphere(a.transform.position, (a.GetComponent<ParticleSystem>()).MaxRadius)) != ContainmentType.Disjoint) return true;
	if (a.renderModel.loadedModel == null) return false;

	BoundingSphere S;
	float max;
	foreach (ModelMesh mm in a.renderModel.loadedModel.Meshes)
	{
		max = Mathf.Max(Mathf.Max(Math.Abs(a.transform.scale.X), Math.Abs(a.transform.scale.Y)), Math.Abs(a.transform.scale.Z));
		S = new BoundingSphere(Vector3.Transform(mm.BoundingSphere.Center, a.transform.Matrix), mm.BoundingSphere.Radius * max);

		if (b.Contains(S) != ContainmentType.Disjoint) return true;
	}

	return false;
}


public static bool Intersects(Ray ray, Collider c, out RaycastHit hitInfo)
{
	float? distance;
	hitInfo = new RaycastHit();
	RaycastHit hitInfoTmp;

	if (c.isBounding)
	{
		distance = ray.Intersects(c.boundingSphere.Transform(c.Actor.transform.Matrix));

		if (distance != null)
		{
			distance = float.MaxValue;
			bool ok = false;
			foreach (Collider col in c.GetDescendantColliders())
			{
				if (Intersects(ray, col, out hitInfoTmp))
				{
					if (hitInfoTmp.distance < distance)
					{
						hitInfo = hitInfoTmp;
						distance = hitInfoTmp.distance;
						ok = true;
					}
				}
			}

			return ok;
		}
	}
	else if (c.box)
	{
		hitInfo.distance = new OrientedBoundingBox(
		c.boundingBox,
		c.Actor.transform.Matrix)
		.Intersects(ray, out hitInfo.point, out hitInfo.normal);
		if (hitInfo.distance >= 0.0f)
		{
			hitInfo.collider = c;
			return true;
		}
	}
	else
	{
		distance = ray.Intersects(c.boundingSphere.Transform(c.Actor.transform.Matrix));

		if (distance != null)
		{
			hitInfo.distance = (float)distance;
			hitInfo.collider = c;
			hitInfo.point = ray.Position + ray.Direction * (float)distance;
			hitInfo.normal = Vector3.Normalize(hitInfo.point - Vector3.Transform(c.boundingSphere.Center, c.Actor.transform.Matrix));

			return true;
		}
	}

	return false;
}


public static bool Intersects(BoundingSphere a, BoundingSphere b, Collision collision)
{
	float distance = Vector3.DistanceSquared(a.Center, b.Center);

	if (distance <= (a.Radius + b.Radius) * (a.Radius + b.Radius))
	{
		distance = (float)Math.Sqrt(distance);

		//normal point
		Vector3 tmp = a.Center - b.Center;
		tmp.Normalize();
		collision.normal = tmp;

		//collision point
		tmp *= (a.Radius + b.Radius - distance) / 2.0f;
		tmp += a.Center;
		collision.point = tmp;

		//overlapping
		collision.overlapping = a.Radius + b.Radius - distance;

		return true;
	}
	return false;
}


public static bool Raycast(Ray ray, out RaycastHit hitInfo, uint mask = (uint)Layer.All)
{
	int bestI = 0;
	float bestDist = float.MaxValue;

	List<RaycastHit> hits = new List<RaycastHit>();

	foreach (var layer in PhysicsMgr.instance.layers.Values)
	{
		if (layer.IsIn(mask) == false) continue;

		foreach (var col in layer.colliders.Values)
			if (Intersects(ray, col, out hitInfo))
				hits.Add(hitInfo);

		foreach (var tmp in layer.rbs.Values)
			if (Intersects(ray, tmp.Actor.collider, out hitInfo))
				hits.Add(hitInfo);
	}

	if (hits.Count == 0)
	{
		hitInfo = new RaycastHit();
		return false;
		}

		for (int i = 0; i < hits.Count; ++i)
		{
			if (hits[i].distance < bestDist)
			{
				bestDist = hits[i].distance;
				bestI = i;
			}
		}

		hitInfo = hits[bestI];
		return true;
	}
}
*/

/*


class MathPhys
{
	// Helper variables
	static float minDist, maxDist, ood, t1, t2, tmp;
	
	//distance from point to plane
	public static float DistPointPlane(Vector3 q, Plane p)
	{
		return Dot(q, p.Normal) - p.D;
	}
	
	// Returns the squared distance between point c and segment ab
	public static float SqDistPointSegment(Vector3 a, Vector3 b, Vector3 c)
	{
		Vector3 ab = b - a;
		Vector3 ac = c - a;
		Vector3 bc = c - b;

		float e = Dot(ac, ab);
		// Handle cases where c projects outside ab
		if (e <= 0.0f) return Dot(ac, ac);
		float f = Dot(ab, ab);
		if (e >= f) return Dot(bc, bc);
		// Handle cases where c projects onto ab
		return Dot(ac, ac) - e * e / f;
	}
	
	// Computes the square distance between a point p and an AABB b
	public static float SqDistPointAABB(Vector3 p, BoundingBox b)
	{
		float sqDist = 0.0f;

		if (p.X < b.Min.X) sqDist += (b.Min.X - p.X) * (b.Min.X - p.X);
		else if (p.X > b.Max.X) sqDist += (p.X - b.Max.X) * (p.X - b.Max.X);

		if (p.Y < b.Min.Y) sqDist += (b.Min.Y - p.Y) * (b.Min.Y - p.Y);
		else if (p.Y > b.Max.Y) sqDist += (p.Y - b.Max.Y) * (p.Y - b.Max.X);

		if (p.Z < b.Min.Z) sqDist += (b.Min.Z - p.Z) * (b.Min.Z - p.Z);
		else if (p.Z > b.Max.Z) sqDist += (p.Z - b.Max.Z) * (p.X - b.Max.Z);

		return sqDist;
	}

	// Computes the square distance between point p and OBB b
	public static float SqDistPointOBB(Vector3 p, OBB b)
	{
		Vector3 closest;
		ClosestPtPointOBB(p, b, out closest);
		float sqDist = Dot(closest - p, closest - p);
		return sqDist;
	}

	//Given line pq and ccw triangle abc, return whether line pierces triangle. If
	//so, also return the barycentric coordinates (u,v,w) of the intersection point
	public static bool IntersectLineTriangle(Vector3 p, Vector3 q, Vector3 a, Vector3 b, Vector3 c, out Vector3 intersection)
	{
		Vector3 pq = q - p;
		Vector3 pa = a - p;
		Vector3 pb = b - p;
		Vector3 pc = c - p;
		// Test if pq is inside the edges bc, ca and ab. Done by testing
		// that the signed tetrahedral volumes, computed using scalar triple
		// products, are all positive
		float u = ScalarTriple(pq, pc, pb);
		if (u < 0.0f) { intersection = Vector3.Zero; return false; }
		float v = ScalarTriple(pq, pa, pc);
		if (v < 0.0f) { intersection = Vector3.Zero; return false; }
		float w = ScalarTriple(pq, pb, pa);
		if (w < 0.0f) { intersection = Vector3.Zero; return false; }
		// Compute the barycentric coordinates (u, v, w) determining the
		// intersection point r, r = u*a + v*b + w*c
		float denom = 1.0f / (u + v + w);
		u *= denom;
		v *= denom;
		w *= denom; // w = 1.0f - u - v;
		intersection = u * a + v * b + w * c;
		return true;
	}

	public static float TestRayAABB(Ray ray, BoundingBox box, out Vector3 q, out Vector3 n)
	{
		q = n = Vector3.Zero;
		minDist = 0.0f;
		maxDist = float.MaxValue;

		// If ray is parrarel to any axis, and point is outside its slab, no intersection
		if (Abs(ray.Direction.X) < 0.0001f && (ray.Position.X < box.Min.X || ray.Position.X < box.Max.X)) return -1.0f;
		if (Abs(ray.Direction.Y) < 0.0001f && (ray.Position.Y < box.Min.Y || ray.Position.Y < box.Max.Y)) return -1.0f;
		if (Abs(ray.Direction.Z) < 0.0001f && (ray.Position.Z < box.Min.Z || ray.Position.Z < box.Max.Z)) return -1.0f;

		// Test X axis
		ood = 1.0f / ray.Direction.X;
		t1 = (box.Min.X - ray.Position.X) * ood;
		t2 = (box.Max.X - ray.Position.X) * ood;

		if (t1 > t2) { tmp = t1; t1 = t2; t2 = tmp; }
		if (t1 > minDist) minDist = t1;
		if (t2 < maxDist) maxDist = t2;
		if (minDist > maxDist) return -1.0f;

		// Test Y axis
		ood = 1.0f / ray.Direction.Y;
		t1 = (box.Min.Y - ray.Position.Y) * ood;
		t2 = (box.Max.Y - ray.Position.Y) * ood;

		if (t1 > t2) { tmp = t1; t1 = t2; t2 = tmp; }
		if (t1 > minDist) minDist = t1;
		if (t2 < maxDist) maxDist = t2;
		if (minDist > maxDist) return -1.0f;

		// Test Z axis
		ood = 1.0f / ray.Direction.Z;
		t1 = (box.Min.Z - ray.Position.Z) * ood;
		t2 = (box.Max.Z - ray.Position.Z) * ood;

		if (t1 > t2) { tmp = t1; t1 = t2; t2 = tmp; }
		if (t1 > minDist) minDist = t1;
		if (t2 < maxDist) maxDist = t2;
		if (minDist > maxDist) return -1.0f;

		// Ray intersects all 3 slabs. Return point (q) and intersection distance (tmin)
		q = ray.Position + ray.Direction * minDist;
		ClosestNormPointAABB(q - ray.Direction * 0.0001f, box, out n);

		return minDist;
	}
}
}
*/