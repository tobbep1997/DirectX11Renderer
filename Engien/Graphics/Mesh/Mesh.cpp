#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::SetMesh(std::vector<VERTEX> v)
{
	this->vertex = v;
	this->_createBuffer(this->vertex.data(), static_cast<int>(this->vertex.size()));
}
