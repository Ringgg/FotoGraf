#include "stdafx.h"
#include "LightIntensity.h"

void LightIntensity::Add(double R, double G, double B)
{
	r += R; g += G; b += B;
	ClampValues();
}

LightIntensity LightIntensity::operator+(LightIntensity & li)
{
	LightIntensity result(r + li.r, g + li.g, b + li.b);
	result.ClampValues();
	return result;
}

LightIntensity LightIntensity::operator-(LightIntensity & li)
{
	LightIntensity result(r - li.r, g - li.g, b - li.b);
	result.ClampValues();
	return result;
}

LightIntensity LightIntensity::operator/(float num)
{
	num = 1 / num;
	return LightIntensity(r * num, g * num, b * num);
}

void LightIntensity::operator+=(LightIntensity & li)
{
	r += li.r; g += li.g; b += li.b;
	ClampValues();
}

void LightIntensity::operator-=(LightIntensity & li)
{
	r -= li.r; g -= li.g; b -= li.b;
	ClampValues();
}

void LightIntensity::operator*=(float num)
{
	r *= num; g *= num; b *= num;
	ClampValues();
}

void LightIntensity::operator/=(float num)
{
	num = 1 / num;
	r *= num; g *= num; b *= num;
	ClampValues();
}

LightIntensity operator*(float num, LightIntensity & li)
{
	return LightIntensity(li.r * num, li.g * num, li.b * num);
}

LightIntensity operator*(LightIntensity & li, float num)
{
	return LightIntensity(li.r * num, li.g * num, li.b * num);
}

std::ostream & operator<<(std::ostream & str, LightIntensity & li)
{
	return str << "LightIntensity{R:" << li.r << ",G:" << li.g << ",B:" << li.b << "}";
}
