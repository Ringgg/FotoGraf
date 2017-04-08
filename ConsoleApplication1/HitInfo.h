#pragma once

struct HitInfo
{
	Float3 p;
	Float3 n;
	float d;

	~HitInfo();
	HitInfo();
	HitInfo(Float3 point, Float3 normal, float distance = 1000000);
};

