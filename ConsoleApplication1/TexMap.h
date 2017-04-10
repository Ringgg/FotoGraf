#pragma once
class TexMap
{
public:

	// spherical mapping
	inline static Float3 GetTextureCoords(Float3& hit)
	{
		static double theta, phi, u, v;
		static Float3 result;

		theta = acos(hit.y);
		phi = atan2(hit.x, hit.z);

		if (phi < 0.0) phi += 6.28318;

		result.y = phi * 0.159154; // u
		result.x = 1.0 - theta * 0.318309; // v

		return result;
	};

	// bugged
	inline static Float3 GetTextureCoords(Float3& hit, Triangle& t)
	{
		static double invDetT, r1, r2, r3;
		static Float3 result;

		invDetT = 1/((t.y.y - t.z.y)*(t.x.x - t.z.x) + (t.z.x - t.y.x)*(t.x.y - t.z.y));
		r1 = invDetT * ((t.y.y-t.z.y)*(hit.x-t.z.x) - (t.z.x-t.y.x)*(hit.y-t.z.y));
		r2 = invDetT * ((t.z.y-t.x.y)*(hit.x-t.z.x) - (t.x.x-t.z.x)*(hit.y-t.z.y));
		r3 = 1 - r1 - r2;

		result.y = (r1 * t.UVx.y) + (r2 * t.UVy.y) + (r3 * t.UVz.y); // u
		result.x = (r1 * t.UVx.x) + (r2 * t.UVy.x) + (r3 * t.UVz.x); // v

		return result;
	}

private:
	TexMap();
	~TexMap();
};