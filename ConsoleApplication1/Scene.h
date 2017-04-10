#pragma once

class Scene
{
public:
	Scene();

	vector<Shape*> shapes;
	vector<Light*> lights;
	Camera* camera;

	void Render(string path);
};