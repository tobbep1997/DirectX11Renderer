#pragma once
#include <vector>
#include "../../Window/Structs.h"
#include "../Drawable.h"
class Mesh :
	public Drawable
{
private:
	std::vector<VERTEX> vertex;
public:
	Mesh();
	~Mesh();

	void SetMesh(std::vector<VERTEX> v);
	
};

