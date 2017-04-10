#pragma once

typedef bitmap_image Texture;

struct Material
{
	string name;
	Color ambient, diffuse, specular;
	uint16_t shininess;					
	Texture texture;
};