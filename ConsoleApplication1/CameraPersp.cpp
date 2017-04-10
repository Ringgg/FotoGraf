#include "stdafx.h"
#include "CameraPersp.h"

#define MAX_DEPTH 3

CameraPersp::CameraPersp() { }

CameraPersp::CameraPersp(int x, int y, double fow, double near, double far,
						 Float3 & pos, Float3 & dir, Float3 & up)
					   : Camera(x, y, pos), nearPlane(near), farPlane(far)
{
	fow *= 0.017453225;
	fowX = fow;
	fowY = fow * sizeY / sizeX;

	w = dir.Normalized(); // forward
	u = Linear::Cross(w, up).Normalized(); // side
	v = Linear::Cross(w, u); // up

	a = u * 2 * nearPlane * tan(fowY * 0.5);
	b = v * 2 * nearPlane * tan(fowX * 0.5);
	c = w * nearPlane - (a + b) * 0.5;
}

void CameraPersp::Render(bitmap_image & img)
{
	invSizeX = 1.0F / sizeX;
	invSizeY = 1.0F / sizeY;
	img.setwidth_height(sizeX, sizeY);
	for (int i = 0; i < sizeX; ++i)
		for (int j = 0; j < sizeY; ++j)
			RenderPixel(i, j, img);
}

void CameraPersp::RenderPixel(double x, double y, bitmap_image & image)
{
	static Ray ray;
	static Color light;

	ray.origin = position;
	ray.direction = (c + a * (x * invSizeX) + b * (y * invSizeY)).Normalized();
	
	light = TestSquare(x, y, 0.1, 0);
	image.set_pixel(x, y, light);
}

Color CameraPersp::TestColor(Ray & ray)
{
	static HitInfo hit;
	static PhongColor tmpColor, baseColor, result;
	static uint64_t texX, texY;
	static Float3 texUV;
	
	if (!Linear::Raycast(ray, scene->shapes, hit))
		return backgroundColor;

	static Triangle test;
	test = Triangle(
		Float3(0,0,0), Float3(4,0,0), Float3(0,4,0), 
		Float3(0,0,0), Float3(1,0,0), Float3(0,1,0));

	// texture mapping
	texUV = TexMap::GetTextureCoords(hit.p, test); // todo: find triangle hit
	texUV.x = fmod(texUV.x, 1);
	texUV.y = fmod(texUV.y, 1);
	texUV.z = fmod(texUV.z, 1);

	texX = (int)((hit.objHit->material->texture.width() - 1)*texUV.x);
	texY = (int)((hit.objHit->material->texture.height()- 1)*texUV.y);
	hit.objHit->material->texture.get_pixel(texX, texY, baseColor.diffuse);
	hit.objHit->material->texture.get_pixel(texX, texY, baseColor.specular);

	result.ambient = hit.objHit->material->ambient;
	result.diffuse *= 0;
	result.specular *= 0;

	//light calculation
	for (int i = 0; i < scene->lights.size(); ++i)
	{
		tmpColor = baseColor;
		scene->lights[i]->TestColor(ray, hit, scene->shapes, tmpColor);
		result.diffuse += tmpColor.diffuse;
		result.specular += tmpColor.specular;
	}

	return result.ambient + result.diffuse + result.specular;
}

Color CameraPersp::TestSquare(double x, double y, double treshold, int depth)
{
	static double invs[]{ 0.25, 0.125, 0.0625, 0.03125 };
	static Ray ray;
	static Color intens[4];
	static double minR, maxR, minG, maxG, minB, maxB, maxDist;
	minR = minG = minB = 1;
	maxR = maxG = maxB = 0;

	ray.origin = position;

	// left down
	ray.direction = (c + a * ((x - invs[depth]) * invSizeX) + b * ((y - invs[depth]) * invSizeX)).Normalized();
	intens[0] = TestColor(ray); 
	// left up
	ray.direction = (c + a * ((x - invs[depth]) * invSizeX) + b * ((y + invs[depth]) * invSizeX)).Normalized();
	intens[1] = TestColor(ray);
	// right down
	ray.direction = (c + a * ((x + invs[depth]) * invSizeX) + b * ((y - invs[depth]) * invSizeX)).Normalized();
	intens[2] = TestColor(ray);
	// right up
	ray.direction = (c + a * ((x + invs[depth]) * invSizeX) + b * ((y + invs[depth]) * invSizeX)).Normalized();
	intens[3] = TestColor(ray);

	for (int i = 0; i < 4; ++i)
	{
		if (intens[i].r < minR) minR = intens[i].r; if (intens[i].r > maxR) minR = intens[i].r;
		if (intens[i].g < minG) minG = intens[i].g; if (intens[i].g > maxG) minG = intens[i].g;
		if (intens[i].b < minB) minB = intens[i].b; if (intens[i].b > maxB) minB = intens[i].b;
	}

	maxDist = maxR + maxG + maxB - minR - minG - minB;

	if (depth < MAX_DEPTH && maxDist > treshold)
	{
		intens[0] = TestSquare((x - invs[depth]), (y - invs[depth]), treshold, depth + 1);
		intens[1] = TestSquare((x - invs[depth]), (y + invs[depth]), treshold, depth + 1);
		intens[2] = TestSquare((x + invs[depth]), (y - invs[depth]), treshold, depth + 1);
		intens[3] = TestSquare((x + invs[depth]), (y + invs[depth]), treshold, depth + 1);
	}

	return intens[0] * 0.25 + intens[1] * 0.25 + intens[2] * 0.25 + intens[3] * 0.25;
}
