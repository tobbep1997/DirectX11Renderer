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
	struct FACE
	{
		bool quad;
		int v1, v2, v3, v4;
		int t1, t2, t3, t4;
		int n1, n2, n3, n4;
	};
	static std::vector<std::vector<VERTEX>> _loadMesh(const wchar_t * path);
public:
	MeshLoader();
	~MeshLoader();

	static std::vector<std::vector<VERTEX>> LoadMesh(const std::string & path);
};

