#include "stdafx.h"
#include "ObjReader.h"

ObjReader::ObjReader() { }
ObjReader::ObjReader(const ObjReader &p) 
{
	verts = p.verts;
	norms = p.norms;
	UVs = p.UVs;
	tris = p.tris;
	currentMaterial = p.currentMaterial;
	currentGroup = p.currentGroup;
}

Mesh ObjReader::loadMesh(string path)
{
	file.open(path, ios::in);

	while (!file.eof())
	{
		if (ReadLine() != 0)
		{
			cout << "OBJ parsing error\n";
			break;
		}
	}

	return Mesh(tris);
}

int ObjReader::ReadLine()
{
	static string type;
	file >> type;

	if (file.eof()) return 0;
	else if (type == "#") { getline(file, type); return 0; }
	else if (type == "v") return ReadVerticle();
	else if (type == "vt") return ReadNormal();
	else if (type == "vn") return ReadTexture();
	else if (type == "g") return ReadGroup();
	else if (type == "f") return ReadFace();
	else if (type == "mtlib") return ReadMatFile();
	else if (type == "usemtl") return ReadUseMaterial();
	else return -1;
	return 0;
}

int ObjReader::ReadVerticle() 
{
	static Float3 point;
	file >> point.x >> point.y >> point.z;
	verts.push_back(point);
	return 0;
}

int ObjReader::ReadNormal()
{
	static Float3 point;
	file >> point.x >> point.y >> point.z;
	norms.push_back(point);
	return 0;
}

int ObjReader::ReadTexture()
{
	static Float3 point;
	file >> point.x >> point.y >> point.z;
	UVs.push_back(point);
	return 0;
}

int ObjReader::ReadGroup()
{
	getline(file, currentGroup);
	return 0;
}

int ObjReader::ReadFace()
{
	static int vIndexes[3];
	static int nIndexes[3];
	static int tIndexes[3];
	static vector<int> temp;
	static string next;
	static FaceType fs;

	for (int i = 0; i < 3; ++i)
	{
		file >> next;
		fs = GetFaceType(next);
		if (fs == geo)
		{
			vIndexes[i] = stoi(next);
		}
		if (fs == geoNor)
		{
			temp = SplitIntoIndices(fs, next);
			assert(temp.size() == 2);
			vIndexes[i] = temp[0];
			nIndexes[i] = temp[1];
		}
		if (fs == geoTexNor)
		{
			temp = SplitIntoIndices(fs, next);
			assert(temp.size() == 3);
			vIndexes[i] = temp[0];
			tIndexes[i] = temp[1];
			nIndexes[i] = temp[2];
		}
	}

	tris.push_back(
		Triangle(
			verts[vIndexes[0] - 1],
			verts[vIndexes[1] - 1],
			verts[vIndexes[2] - 1]));

	return 0;
}

int ObjReader::ReadMatFile() { return 0; }
int ObjReader::ReadUseMaterial() { return 0; }

FaceType ObjReader::GetFaceType(string& s)
{
	if (s.find("//") != string::npos)		return geoNor;
	else if (s.find("/") != string::npos)	return geoTexNor;
	else									return geo;
}

vector<int> ObjReader::SplitIntoIndices(FaceType fs, string& s) 
{
	static string separator, index;
	vector<int> indices;
	int next = 0;

	separator = (fs == FaceType::geoNor) ? "//" : "/";

	while ((next = s.find(separator)) != string::npos)
	{
		index = s.substr(0, next);
		indices.push_back(stoi(index));
		s.erase(0, next + separator.length());
	}
	if (!s.empty())
	{
		indices.push_back(stoi(s));
	}

	return indices;
}
