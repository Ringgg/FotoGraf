#pragma once

class Scene
{
public:
	Scene();

	vector<Shape*> shapes;
	Camera* camera;

	void Render(string path);
};