#pragma once

class Camera
{
public:
	Camera();
	Camera(int x, int y, Float3& pos);

	Scene* scene;
	int sizeX, sizeY;
	Float3 position;
	LightIntensity backgroundColor;

	virtual void Render(bitmap_image& img) = 0;
	void Init(Scene& s) { scene = &s; }

protected:
	virtual void RenderPixel(float x, float y, bitmap_image& image) = 0;
};

