#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh() { }
Mesh::Mesh(vector<Triangle>& tris) : tris(tris) { }

bool Mesh::IntersectsWith(Ray & ray, HitInfo & info)
{
	for (int i = 0; i < tris.size(); ++i)
	{
		if (Linear::Intersects(ray, tris[i], info))
		{
			info.objHit = this;
			return true;
		}
	}
	return false;
}
