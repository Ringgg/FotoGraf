#pragma once

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>

enum FaceType 
{
	geo,		// a
	geoNor,		// a//b
	geoTexNor,	// a/b/c
};

class ObjReader
{
private:
	ifstream file;
	vector<Float3> verts;
	vector<Float3> norms;
	vector<Float3> UVs;
	vector<Triangle> tris;
	Material currentMaterial;
	string currentGroup;
	map<string, Float3*> groups;

	int ReadLine();
	int ReadVerticle();
	int ReadNormal();
	int ReadTexture();
	int ReadGroup();
	int ReadFace();
	int ReadMatFile();
	int ReadUseMaterial();
	FaceType GetFaceType(string& str);
	vector<int> SplitIntoIndices(FaceType fs, string& s);

public:
	ObjReader();
	ObjReader(const ObjReader& p);
	Mesh loadMesh(string path);
};