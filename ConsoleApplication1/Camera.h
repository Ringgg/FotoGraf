#pragma once

class Camera
{
public:
	Camera();
	Camera(int x, int y, Float3& pos);

	Scene* scene;
	int sizeX, sizeY;
	double invSizeX, invSizeY;
	Float3 position;
	Color backgroundColor;

	virtual void Render(bitmap_image& img) = 0;
	void Init(Scene& s) { scene = &s; }

protected:
	virtual void RenderPixel(double x, double y, bitmap_image& image) = 0;
};

