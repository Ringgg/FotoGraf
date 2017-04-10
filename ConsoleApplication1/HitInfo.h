#pragma once

struct HitInfo
{
	Shape* objHit;
	Float3 p;
	Float3 n;
	double d;

	~HitInfo();
	HitInfo();
	HitInfo(Float3 point, Float3 normal, double distance = 1000000);
};

