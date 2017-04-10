#include "stdafx.h"
#include "Color.h"

void Color::Add(double R, double G, double B)
{
	r += R; g += G; b += B;
	ClampValues();
}

Color Color::operator+(Color & li)
{
	Color result(r + li.r, g + li.g, b + li.b);
	result.ClampValues();
	return result;
}

Color Color::operator-(Color & li)
{
	Color result(r - li.r, g - li.g, b - li.b);
	result.ClampValues();
	return result;
}

Color Color::operator/(double num)
{
	num = 1 / num;
	return Color(r * num, g * num, b * num);
}

void Color::operator+=(Color & li)
{
	r += li.r; g += li.g; b += li.b;
	ClampValues();
}

void Color::operator-=(Color & li)
{
	r -= li.r; g -= li.g; b -= li.b;
	ClampValues();
}

void Color::operator*=(Color & li)
{
	r *= li.r; g *= li.g; b *= li.b;
}

void Color::operator*=(double num)
{
	r *= num; g *= num; b *= num;
	ClampValues();
}

void Color::operator/=(double num)
{
	num = 1 / num;
	r *= num; g *= num; b *= num;
	ClampValues();
}

Color operator*(double num, Color & li)
{
	return Color(li.r * num, li.g * num, li.b * num);
}

Color operator*(Color & li, double num)
{
	return Color(li.r * num, li.g * num, li.b * num);
}

Color operator*(Color & ls, Color & rs)
{
	return Color(ls.r * rs.r, ls.g * rs.g, ls.b * rs.b);
}

std::ostream & operator<<(std::ostream & str, Color & li)
{
	return str << "LightIntensity{R:" << li.r << ",G:" << li.g << ",B:" << li.b << "}";
}
