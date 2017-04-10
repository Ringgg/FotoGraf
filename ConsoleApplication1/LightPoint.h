#pragma once
class LightPoint : public Light
{
public:
	LightPoint();
	LightPoint(const LightPoint& light);
	LightPoint(Float3 position, Color color);

	Float3 position;

	void TestColor(Ray & ray, HitInfo & hit, vector<Shape*>& shapes,
		PhongColor& color);
protected:
	bool IsInShadow(Float3 pt, vector<Shape*>& shapes);
};

