#include "stdafx.h"
#include "Scene.h"

Scene::Scene() { }

void Scene::Render(std::string path)
{
	if (camera == nullptr)
	{
		cout << "camera is null";
		return;
	}
	bitmap_image img;
	camera->Render(img);
	img.save_image(path);
}
