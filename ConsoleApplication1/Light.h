#pragma once
class Light
{
public:
	Light();
	Light(const Light& light);
	Light(Color c);
	
	Color color;

	virtual void TestColor(Ray & ray, HitInfo & hit, vector<Shape*>& shapes,
		PhongColor& color) = 0;

	void Phong(
		Float3& Lightdir, Float3& LookDir, Float3& normal,
		Color& diffuse, Color& specular,
		Material* mat);

protected:
	virtual bool IsInShadow(Float3 pt, vector<Shape*>& shapes) = 0;
};