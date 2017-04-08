#include "stdafx.h"
#include "Plane.h"


Plane::~Plane() { }
Plane::Plane(Float3 norm, float dist): normal(norm), distance(dist)
{
	normal.Normalize();
}
