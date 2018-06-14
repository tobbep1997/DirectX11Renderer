#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::SetMesh(std::vector<VERTEX> v)
{
	this->vertex.push_back(v);
	this->_createBuffer(this->vertex[0].data(), static_cast<int>(this->vertex[0].size()));
}

void Mesh::SetMeshes(MESH v)
{
	this->vertex = v.vertex;
	this->_createMultBuffer(v);
}
