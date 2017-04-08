#pragma once

struct Float3
{
	float x, y, z;

	~Float3();
	Float3();
	Float3(const Float3& other);
	Float3(float xx, float yy, float zz);

	float& operator[](int index);
	Float3 operator -();
	Float3 operator /(float f);
	void operator+=( Float3& v);
	void operator-=( Float3& v);
	void operator*=( float f);
	void operator/=( float f);
	bool operator==( Float3& v);
	bool operator!=( Float3& v);
	float LengthSquared();
	float Length();
	void Normalize();
	Float3 Normalized();
};

inline std::ostream& operator<<(std::ostream& os, Float3 a) { os << "(" << a.x << "," << a.y << "," << a.z << ")";  return os; }
inline Float3 operator+(Float3& a, Float3& b) { return Float3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Float3 operator-(Float3& a, Float3& b) { return Float3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Float3 operator*(Float3& a, float f) { return Float3(a.x * f, a.y * f, a.z * f); }