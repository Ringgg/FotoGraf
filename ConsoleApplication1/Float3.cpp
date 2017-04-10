#include "stdafx.h"
#include "Float3.h"

Float3::~Float3() { }
Float3::Float3() : x(0), y(0), z(0) { }
Float3::Float3(const Float3& v) : x(v.x), y(v.y), z(v.z) { }
Float3::Float3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) { }
