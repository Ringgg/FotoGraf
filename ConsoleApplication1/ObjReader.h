#pragma once

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

	vector<Mesh*> meshes;
	Mesh* mesh;

	vector<Material*> materials;
	Material* material;

	vector<Float3> verts;
	vector<Float3> norms;
	vector<Float3> UVs;
	string currentGroup;

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
	vector<Mesh*> ObjReader::loadMesh(string path);
};