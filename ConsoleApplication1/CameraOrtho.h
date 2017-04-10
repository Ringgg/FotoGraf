#pragma once

class CameraOrtho : public Camera
{
public:
	CameraOrtho();
	CameraOrtho(int x, int y, double pxSize, Float3& pos, Float3& dir, Float3& up);

	Float3 up;
	Float3 direciton;
	double pixelSize;

private:
	Float3 lu, ld, ru, rd;

public:
	void Render(bitmap_image& img);

protected:
	void RenderPixel(double x, double y, bitmap_image& image);
	Color TestColor(Ray& ray);
	Color TestSquare(Float3 lu, Float3 ld, Float3 ru, Float3 rd, double treshold, double iterations);
};

