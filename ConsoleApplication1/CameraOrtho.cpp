#pragma once
#include "stdafx.h"
#include "CameraOrtho.h"


CameraOrtho::CameraOrtho(){ }

CameraOrtho::CameraOrtho(int x, int y, float pxSize,
					     Float3& pos, Float3& dir, Float3& u)
					   : Camera(x,y, pos), pixelSize(pxSize), direciton(dir), up(u)
{
	backgroundColor(0.01, 0.01, 0.01);

	Float3 side = Linear::Cross(direciton, up).Normalized();
	Float3 up = Linear::Cross(direciton, side).Normalized();

	float halfsizeX = pxSize * sizeX * 0.5;
	float halfsizeY = pxSize * sizeY * 0.5;

	ld = position - side * halfsizeX - up * halfsizeY;
	lu = position - side * halfsizeX + up * halfsizeY;
	rd = position + side * halfsizeX - up * halfsizeY;
	ru = position + side * halfsizeX + up * halfsizeY;
}

void CameraOrtho::Render(bitmap_image& img)
{
	img.setwidth_height(sizeX, sizeY);
	for (int i = 0; i < sizeX; ++i)
		for (int j = 0; j < sizeY; ++j)
			RenderPixel(i, j, img);
}

void CameraOrtho::RenderPixel(float x, float y, bitmap_image& image)
{
	static Ray ray;
	static Float3 pos1, pos2, pos3, pos4;
	static LightIntensity light;

	pos1 = Linear::Lerp(Linear::Lerp(lu, ru, (x - 0.5) / sizeX), Linear::Lerp(ld, rd, (x - 0.5) / sizeX), (y + 0.5) / sizeY);
	pos2 = Linear::Lerp(Linear::Lerp(lu, ru, (x - 0.5) / sizeX), Linear::Lerp(ld, rd, (x - 0.5) / sizeX), (y - 0.5) / sizeY);
	pos3 = Linear::Lerp(Linear::Lerp(lu, ru, (x + 0.5) / sizeX), Linear::Lerp(ld, rd, (x + 0.5) / sizeX), (y + 0.5) / sizeY);
	pos4 = Linear::Lerp(Linear::Lerp(lu, ru, (x + 0.5) / sizeX), Linear::Lerp(ld, rd, (x + 0.5) / sizeX), (y - 0.5) / sizeY);
	
	light = TestSquare(pos1, pos2, pos3, pos4, 0.1, 3);

	image.set_pixel(x, y, light);
}

LightIntensity CameraOrtho::TestColor(Ray & ray)
{
	static HitInfo cur;
	static HitInfo best;
	best = HitInfo(Float3(), Float3());
	for (int i = 0; i < scene->shapes.size(); ++i)
	{
		if (scene->shapes[i]->IntersectsWith(ray, cur))
		{
			if (cur.d < best.d)
				best = cur;
		}
	}
	//return LightIntensity(1, 1, 1) * (Linear::Dot(ray.direction, best.n));
	if (best.d < 10000)
		return LightIntensity(1, 1, 1) * (Linear::Dot(ray.direction, best.n));
	else				
		return backgroundColor;
}

LightIntensity CameraOrtho::TestSquare(Float3 lu, Float3 ld, Float3 ru, Float3 rd, float treshold = 0.25, float iterations = 3)
{
	static LightIntensity intens[4];
	static float minR, maxR, minG, maxG, minB, maxB, maxDist;

	minR = minG = minB = 1;
	maxR = maxG = maxB = 0;

	intens[0] = TestColor(Ray(lu, direciton)); intens[1] = TestColor(Ray(ld, direciton));
	intens[2] = TestColor(Ray(ru, direciton)); intens[3] = TestColor(Ray(rd, direciton));

	for (int i = 0; i < 4; ++i)
	{
		if (intens[i].r < minR) minR = intens[i].r; if (intens[i].r > maxR) minR = intens[i].r;
		if (intens[i].g < minG) minG = intens[i].g; if (intens[i].g > maxG) minG = intens[i].g;
		if (intens[i].b < minB) minB = intens[i].b; if (intens[i].b > maxB) minB = intens[i].b;
	}

	maxDist = maxR + maxG + maxB - minR - minG - minB;

	if (--iterations > 0 && (maxDist > treshold))
	{
		intens[0] = TestSquare(lu, Linear::Lerp(lu, ld, 0.5), Linear::Lerp(lu, ru, 0.5), Linear::Lerp(lu, rd, 0.5), treshold, iterations);
		intens[1] = TestSquare(Linear::Lerp(ld, lu, 0.5), ld, Linear::Lerp(ld, ru, 0.5), Linear::Lerp(ld, rd, 0.5), treshold, iterations);
		intens[2] = TestSquare(Linear::Lerp(ru, lu, 0.5), Linear::Lerp(ru, rd, 0.5), ru, Linear::Lerp(ru, rd, 0.5), treshold, iterations);
		intens[3] = TestSquare(Linear::Lerp(rd, lu, 0.5), Linear::Lerp(rd, ld, 0.5), Linear::Lerp(rd, ru, 0.5), rd, treshold, iterations);
	}

	return intens[0]*0.25 + intens[1]*0.25 + intens[2]*0.25 + intens[3]*0.25;
}


