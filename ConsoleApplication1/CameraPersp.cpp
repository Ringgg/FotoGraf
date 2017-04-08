#include "stdafx.h"
#include "CameraPersp.h"

#define MAX_DEPTH 3

CameraPersp::CameraPersp() { }

CameraPersp::CameraPersp(int x, int y, float fow, float near, float far,
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
	img.setwidth_height(sizeX, sizeY);
	for (int i = 0; i < sizeX; ++i)
		for (int j = 0; j < sizeY; ++j)
			RenderPixel(i, j, img);
}

void CameraPersp::RenderPixel(float x, float y, bitmap_image & image)
{
	static Ray ray;
	static LightIntensity light;

	ray.origin = position;
	ray.direction = (c + a * (x / sizeX) + b * (y / sizeY)).Normalized();
	
	//light = TestColor(ray);
	light = TestSquare(x, y, 0.1, 0);
	image.set_pixel(x, y, light);
}

LightIntensity CameraPersp::TestColor(Ray & ray)
{
	static HitInfo cur;
	static HitInfo best;
	best = HitInfo(Float3(), Float3());
	for (int i = 0; i < scene->shapes.size(); ++i)
		if (scene->shapes[i]->IntersectsWith(ray, cur))
			if (cur.d < best.d)
				best = cur;

	//funzies
	//return LightIntensity(1, 1, 1) * (-Linear::Dot(ray.direction, best.n));
	//return LightIntensity(1, 1, 1) * (1 - best.d * 0.05);
		//return LightIntensity((best.n.x + 1) * 0.5, (best.n.y + 1) * 0.5, (best.n.z + 1) * 0.5) * (-Linear::Dot(ray.direction, best.n)) * (1 - best.d * 0.05);

	if (best.d < 10000)
		return LightIntensity((best.n.x + 1) * 0.5, (best.n.y + 1) * 0.5, (best.n.z + 1) * 0.5) * (1.2 - best.d * 0.25);
	else
		return backgroundColor;
}

LightIntensity CameraPersp::TestSquare(float x, float y, float treshold, int depth)
{
	static float invs[]{ 0.25, 0.125, 0.0625, 0.03125 };
	static Ray ray;
	static LightIntensity intens[4];
	static float minR, maxR, minG, maxG, minB, maxB, maxDist;
	minR = minG = minB = 1;
	maxR = maxG = maxB = 0;

	ray.origin = position;

	// left down
	ray.direction = (c + a * ((x - invs[depth]) / sizeX) + b * ((y - invs[depth]) / sizeY)).Normalized();
	intens[0] = TestColor(ray); 
	// left up
	ray.direction = (c + a * ((x - invs[depth]) / sizeX) + b * ((y + invs[depth]) / sizeY)).Normalized();
	intens[1] = TestColor(ray);
	// right down
	ray.direction = (c + a * ((x + invs[depth]) / sizeX) + b * ((y - invs[depth]) / sizeY)).Normalized();
	intens[2] = TestColor(ray);
	// right up
	ray.direction = (c + a * ((x + invs[depth]) / sizeX) + b * ((y + invs[depth]) / sizeY)).Normalized();
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

/*
EngineImage
PerspectiveCamera::renderScene(ViewPlane &plane, LightIntensity &light, Tracer *tracer) 
{
	LightIntensity color;
	std::string name = tracer->sceneName();
	EngineImage image = EngineImage(plane.getWRes(), plane.getHRes(), light,
	name);
	image.resetPixels(light);
	float x, y;
	float d, near;
	Ray ray;
	Vector3 vc, vo;

	ray.setOrigin(eye);
	for(unsigned int r = 0; r < plane.getWRes(); r++)
	{ //up
		for(unsigned int c = 0; c < plane.getHRes(); c++)
		{ //horizontal
			x = plane.getPixSize() * (c - 0.5f *(plane.getHRes() - 1.0f));
			y = plane.getPixSize() * (r - 0.5f *(plane.getWRes() - 1.0f));
			vo = Vector3(x, y, nearPlane) - eye;
			d = vo.length();
			ray.setDirection(Vector3(x, y, d));//+100));
			vo = ray.getDirection().normalize();
			ray.setDirection(vo);
			color = tracer->rayTrace(ray);
			image.setPixel((int)r, (int)c, color);
		}
	}
	return image;
}
*/