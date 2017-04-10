#pragma once

struct HitInfo
{
	Shape* objHit; 
	Triangle* triHit; // triangle hit if any
	Float3 p; // hit point
	Float3 n; // normal
	Float3 uvw; //baricentric triangle hit coords
	double d; // distance from ray origin

	~HitInfo();
	HitInfo();
	HitInfo(Float3 point, Float3 normal, double distance = 1000000);
};

