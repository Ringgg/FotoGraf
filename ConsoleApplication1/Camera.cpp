#include "stdafx.h"
#include "Camera.h"

using namespace std;

Camera::Camera() { }
Camera::Camera(int x, int y, Float3 & pos) : sizeX(x), sizeY(y), position(pos) { }
