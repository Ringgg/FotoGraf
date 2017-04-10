#include "stdafx.h"
#include "Light.h"

Light::Light() { }
Light::Light(const Light & light) : color(light.color) { }
Light::Light(Color c) : color(c) { }

void Light::Phong(
	Float3& Lightdir, Float3& LookDir, Float3& normal,
	Color& diffuse, Color& specular,
	Material* mat)
{
	static double specForce;

	//diffuse
	diffuse = diffuse * mat->diffuse * color * Linear::Dot(-Lightdir, normal);

	//specular
	specForce = Linear::Dot(LookDir, Linear::Reflect(Lightdir, normal));
	if (specForce < 0) specForce = 0;
	specular = specular * mat->specular * color * pow(specForce, mat->shininess);
}
