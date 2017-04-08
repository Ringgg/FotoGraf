#include "stdafx.h"
#include "Float3.h"

Float3::~Float3() { }
Float3::Float3() : x(0), y(0), z(0) { }
Float3::Float3(const Float3& v) : x(v.x), y(v.y), z(v.z) { }
Float3::Float3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) { }

float& Float3::operator[](int index) { return *((float*)this + index); }
Float3 Float3::operator-() { return Float3(-x, -y, -z); }
Float3 Float3::operator/(float f)
{
	if (f == 0) return Float3();
	float inv = 1.0f / f;
	return Float3(x * inv, y * inv, z * inv);
}
void Float3::operator+=(Float3& v) { x += v.x; y += v.y; z += v.z; }
void Float3::operator-=(Float3& v) { x -= v.x; y -= v.y; z -= v.z; }
void Float3::operator*=(float f) { x *= f; y *= f; z *= f; }
void Float3::operator/=(float f)
{
	if (f == 0) return;
	float inv = 1.0f / f;
	x *= inv; y *= inv; z *= inv;
}
bool Float3::operator==(Float3& v) { return x == v.x && y == v.y && z == v.z;}
bool Float3::operator!=(Float3& v) { return x != v.x || y != v.y || z != v.z;}
float Float3::LengthSquared() { return x*x + y*y + z*z; }
float Float3::Length() { return sqrtf(x*x + y*y + z*z); }

void Float3::Normalize()
{
	float invLen = 1 / Length();
	x *= invLen; y *= invLen; z *= invLen;
}

Float3 Float3::Normalized()
{
	float invLen = 1 / Length();
	return Float3(x * invLen, y * invLen, z * invLen);
}
