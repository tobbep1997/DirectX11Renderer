#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "../../Window/Structs.h"
#include "Mesh.h"

#include <DirectXMath.h>

class MeshLoader
{
private:
	static std::vector<VERTEX> _loadMesh(const wchar_t * path);
public:
	MeshLoader();
	~MeshLoader();

	static std::vector<VERTEX> LoadMesh(const std::string & path);
};

