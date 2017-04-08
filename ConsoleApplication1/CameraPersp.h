#pragma once
class CameraPersp : public Camera
{
private:
	float fowX, fowY, nearPlane, farPlane;
	Float3 u, v, w, a, b, c;

public:
	CameraPersp();
	CameraPersp(int x, int y, float fow, float near, float far, Float3& pos, Float3& dir, Float3& u);

	void Render(bitmap_image& img);
	
protected:
	void RenderPixel(float x, float y, bitmap_image& image);
	LightIntensity TestColor(Ray& ray);
	LightIntensity TestSquare(float x, float y, float treshold, int depth);
};

