#include "stdafx.h"
#include "HitInfo.h"


HitInfo::HitInfo() { }
HitInfo::HitInfo(Float3 point, Float3 normal, float distance) : p(point), n(normal), d(distance) { }
HitInfo::~HitInfo() { }
