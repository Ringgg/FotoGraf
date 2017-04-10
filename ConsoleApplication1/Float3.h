#pragma once

struct Float3
{
	double x, y, z;

	~Float3();
	Float3();
	Float3(const Float3& other);
	Float3(double xx, double yy, double zz);

	inline double& operator[](int index) { return *((double*)this + index); }
	inline Float3 operator -() { return Float3(-x, -y, -z); }
	inline Float3 operator /(double f)
	{
		static double inv;
		if (f == 0) return Float3();
		inv = 1.0f / f;
		return Float3(x * inv, y * inv, z * inv);
	}
	inline void operator+=( Float3& v) { x += v.x; y += v.y; z += v.z; }
	inline void operator-=( Float3& v) { x -= v.x; y -= v.y; z -= v.z; }
	inline void operator*=( double f) { x *= f; y *= f; z *= f; }
	inline void operator/=( double f)
	{
		static double inv;
		if (f == 0) return;
		inv = 1.0f / f;
		x *= inv; y *= inv; z *= inv;
	}
	inline bool operator==( Float3& v) { return x == v.x && y == v.y && z == v.z; }
	inline bool operator!=( Float3& v) { return x != v.x || y != v.y || z != v.z; }
	inline double LengthSquared() { return x*x + y*y + z*z; }
	inline double Length() { return sqrt(x*x + y*y + z*z); }

	inline void Normalize()
	{
		static double inv;
		inv = 1 / Length();
		x *= inv; y *= inv; z *= inv;
	}

	inline Float3 Normalized()
	{
		static double inv;
		inv = 1 / Length();
		return Float3(x * inv, y * inv, z * inv);
	}
};

inline std::ostream& operator<<(std::ostream& os, Float3 a) { os << "(" << a.x << "," << a.y << "," << a.z << ")";  return os; }
inline Float3 operator+(Float3& a, Float3& b) { return Float3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Float3 operator-(Float3& a, Float3& b) { return Float3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Float3 operator*(Float3& a, double f) { return Float3(a.x * f, a.y * f, a.z * f); }