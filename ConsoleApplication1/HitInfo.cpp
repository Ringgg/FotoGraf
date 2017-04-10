#include "stdafx.h"
#include "HitInfo.h"


HitInfo::HitInfo() { }
HitInfo::HitInfo(Float3 point, Float3 normal, double distance) : p(point), n(normal), d(distance) { }
HitInfo::~HitInfo() { }
