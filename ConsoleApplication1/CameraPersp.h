#pragma once
class CameraPersp : public Camera
{
private:
	double fowX, fowY, nearPlane, farPlane;
	Float3 u, v, w, a, b, c;

public:
	CameraPersp();
	CameraPersp(int x, int y, double fow, double near, double far, Float3& pos, Float3& dir, Float3& u);

	void Render(bitmap_image& img);
	
protected:
	void RenderPixel(double x, double y, bitmap_image& image);
	Color TestColor(Ray& ray);
	Color TestSquare(double x, double y, double treshold, int depth);
};

