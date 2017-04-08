#pragma once

struct LightIntensity
{
	double r, g, b;

	LightIntensity(double R, double G, double B) : r(R), g(G), b(B) {}
	LightIntensity(double R, double G) : r(R), g(G), b(0) {}
	LightIntensity(double R) : r(R), g(0), b(0) {}
	LightIntensity() : r(0), g(0), b(0) {}

	void operator()(float R, float G, float B) { r = R; g = G; b = B; }
	void operator()(float R, float G) { r = R; g = G; b = 0.0; }
	void operator()(float R) { r = R; g = b = 0.0; }

	void Add(double R, double G, double B);

	LightIntensity operator+(LightIntensity &li);
	LightIntensity operator-(LightIntensity &li);
	LightIntensity operator/(float num);
	void operator+=(LightIntensity &li);
	void operator-=(LightIntensity &li);
	void operator*=(float num);
	void operator/=(float num);
	friend LightIntensity operator*(float num, LightIntensity &li);
	friend LightIntensity operator*(LightIntensity &li, float num);
	friend std::ostream& operator<<(std::ostream& str, LightIntensity &li);

	inline void ClampValues()
	{
		if (r > 1) r = 1; else if (r < 0) r = 0;
		if (g > 1) g = 1; else if (g < 0) g = 0;
		if (b > 1) b = 1; else if (b < 0) b = 0;
	}

	static float SqDiff(LightIntensity lhs, LightIntensity rhs)
	{
		lhs -= rhs;
		return lhs.r * lhs.r + lhs.g * lhs.g + lhs.b * lhs.b;
	}
};