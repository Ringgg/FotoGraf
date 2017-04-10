#include "stdafx.h"

void CollTest();
void ImgTest();
void RenderTestOrtho();
void RenderTestPersp();
void ObjTest();
void MeshRenderTest();
void LightTest();
void TextureTest();

int main()
{
	//CollTest();
	//ImgTest();
	//RenderTestOrtho();
	//RenderTestPersp();
	//ObjTest();
	//MeshRenderTest();
	//LightTest();
	TextureTest();
	//cout << "Enter any key: ";
	//getchar();
    return 0;
}

void CollTest()
{
	Ray r1(Float3(0, 0, -10), Float3(0, 0, 1));
	Ray r2(Float3(0, 0, -10), Float3(0, 1, 0));
	Ray r3(Float3(0, -10, -10), Float3(0, 0, 1));

	HitInfo info;
	Sphere s(Float3(), 10);
	Plane p(Float3(0, -1, -1), 0);

	if (Linear::Intersects(r1, s, info))
		cout << r1 << " collided with " << s << " at point: " << info.p << "\n";

	if (Linear::Intersects(r2, s, info))
		cout << r2 << " collided with " << s << " at point: " << info.p << "\n";

	if (Linear::Intersects(r3, s, info))
		cout << r3 << " collided with " << s << " at point: " << info.p << "\n";

	if (Linear::Intersects(r2, p, info))
		cout << r2 << " collided with plane at point: " << info.p << "\n";
}

void ImgTest()
{
	bitmap_image image;
	Color light;
	image.setwidth_height(100, 100, true);

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			light((double)i / 100, (double)j / 100);
			image.set_pixel(i, j, light);
		}
	}

	image.save_image("imgTest.bmp");
}

void RenderTestOrtho()
{
	// camera = CameraOrtho(w, h, pxSize, pos, dir, u); 500,500,0.1, Float3(0,0,-12), Float3(0,0,1), Float3(0,1,0)
	Scene s;
	s.shapes.push_back(new Sphere(Float3(-2, -2, 4), 4));
	s.shapes.push_back(new Sphere(Float3(2, 2, 0), 4));
	s.camera = new CameraOrtho(500, 500, 0.05, Float3(0, 0, -12), Float3(0, 0, 1), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("imgOrthoTest.bmp");
}

void RenderTestPersp()
{
	Scene s;
	s.shapes.push_back(new Sphere(Float3(-2, -2, 4), 4));
	s.shapes.push_back(new Sphere(Float3(2, 2, 0), 4));
	s.camera = new CameraPersp(1000, 1000, 60, 0.1, 1000, Float3(0, 0, -12), Float3(0, 0, 1), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("imgPerspectiveTest.bmp");
}

void ObjTest()
{
	ObjReader reader;
	vector<Mesh*> m = reader.loadMesh("Cube.obj");
	cout << "done loading obj\n";
}

void MeshRenderTest()
{
	ObjReader reader;
	Mesh* m = reader.loadMesh("Cube.obj")[0];
	m->material->diffuse = Color(1, 0.25, 0.25);

	Scene s;
	s.shapes.push_back(m);
	s.camera = new CameraPersp(200, 200, 60, 0.1, 1000, Float3(-1.5, 2.5, -1.5), Float3(0.5, -0.5, 0.5), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("imgMeshRenderTest.bmp");
}

void LightTest()
{
	ObjReader reader;
	
	Sphere sp(Float3(), 0.5);
	Plane p;
	Mesh* m = reader.loadMesh("Cube.obj")[0];
	
	LightPoint lp(Float3(1.1, 4, -2), Color(0.5, 0.5, 0.5));

	sp.material = new Material();
	p.material = new Material();
	sp.material->diffuse = Color(0.25, 1, 0.25);
	p.material->diffuse = Color(1, 1, 1);
	m->material->diffuse = Color(1, 0.25, 0.25);

	Scene s;
	s.shapes.push_back(&sp);
	s.shapes.push_back(m);
	s.shapes.push_back(&p);

	s.lights.push_back(&lp);
	s.camera = new CameraPersp(1000, 1000, 60, 0.1, 1000, Float3(-1.5, 2.5, -1.5), Float3(0.5, -0.5, 0.5), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("imgLightTest.bmp");
}

void TextureTest()
{
	ObjReader reader;

	Mesh* m = reader.loadMesh("CubeTex.obj")[0];
	m->material->shininess = 1;
	m->material->ambient = Color(0.1, 0.1, 0.1);
	m->material->diffuse = Color(1, 1, 1);
	m->material->specular = Color(1, 1, 1);

	Plane* p = new Plane();
	p->material = new Material();
	p->material->shininess = 2;
	p->material->ambient = Color(0.1, 0.1, 0.1);
	p->material->diffuse = Color(0.5, 0.5, 0.5);
	p->material->specular = Color(1, 1, 1);

	Sphere* sp = new Sphere(Float3(), 0.5);
	sp->material = new Material();
	sp->material->texture.load_bitmap("CubeMat.bmp");
	sp->material->shininess = 2;
	sp->material->ambient = Color(0.1, 0.1, 0.1);
	sp->material->diffuse = Color(0.25, 0.25, 0.25);
	sp->material->specular = Color(1, 1, 1);

	LightPoint* lp1 = new LightPoint(Float3(1.1, 4, -2), Color(0.5, 0.5, 0.5));
	LightPoint* lp2 = new LightPoint(Float3(-1.1, 4, 2), Color(0.2, 0.1, 0.1));
	Scene s;

	s.shapes.push_back(m);
	s.shapes.push_back(p);
	s.shapes.push_back(sp);
	s.lights.push_back(lp1);
	s.lights.push_back(lp2);

	s.camera = new CameraPersp(1000, 1000, 60, 0.1, 1000, Float3(-1.5, 2.5, -1.5), Float3(0.5, -0.5, 0.5), Float3(0, 1, 0));
	s.camera->Init(s);

	s.Render("imgLightTest.bmp");
}