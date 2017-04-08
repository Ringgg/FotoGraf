#pragma once

class CameraOrtho : public Camera
{
public:
	CameraOrtho();
	CameraOrtho(int x, int y, float pxSize, Float3& pos, Float3& dir, Float3& up);

	Float3 up;
	Float3 direciton;
	float pixelSize;

private:
	Float3 lu, ld, ru, rd;

public:
	void Render(bitmap_image& img);

protected:
	void RenderPixel(float x, float y, bitmap_image& image);
	LightIntensity TestColor(Ray& ray);
	LightIntensity TestSquare(Float3 lu, Float3 ld, Float3 ru, Float3 rd, float treshold, float iterations);
};

