#pragma once

struct Color
{
	double r, g, b;

	Color(double R, double G, double B) : r(R), g(G), b(B) {}
	Color(double R, double G) : r(R), g(G), b(0) {}
	Color(double R) : r(R), g(0), b(0) {}
	Color() : r(0), g(0), b(0) {}

	void operator()(double R, double G, double B) { r = R; g = G; b = B; }
	void operator()(double R, double G) { r = R; g = G; b = 0.0; }
	void operator()(double R) { r = R; g = b = 0.0; }

	void Add(double R, double G, double B);

	Color operator+(Color &li);
	Color operator-(Color &li);
	Color operator/(double num);
	void operator+=(Color &li);
	void operator-=(Color &li);
	void operator*=(Color &li);
	void operator*=(double num);
	void operator/=(double num);
	friend Color operator*(double num, Color &li);
	friend Color operator*(Color &li, double num);
	friend Color operator*(Color &ls, Color &rs);
	friend std::ostream& operator<<(std::ostream& str, Color &li);

	inline void ClampValues()
	{
		if (r > 1) r = 1; else if (r < 0) r = 0;
		if (g > 1) g = 1; else if (g < 0) g = 0;
		if (b > 1) b = 1; else if (b < 0) b = 0;
	}

	static double SqDiff(Color lhs, Color rhs)
	{
		lhs -= rhs;
		return lhs.r * lhs.r + lhs.g * lhs.g + lhs.b * lhs.b;
	}
};