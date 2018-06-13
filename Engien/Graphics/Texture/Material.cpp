#include "Material.h"




void Material::_loadMTL(const std::wstring & path)
{



}

void Material::_loadTexture(const std::wstring & path)
{
	this->_texture = new Texture();
	this->_texture->LoadTexture(std::string(path.begin(), path.end()));
}

Material::Material(const std::wstring & path)
{
	this->_loadMTL(path);
}

Material::~Material()
{
	delete this->_texture;
}

void Material::LoadMTL(const std::wstring & path)
{
	this->_loadMTL(path);
}

void Material::LoadTexture(const std::wstring & path)
{
	this->_loadTexture(path);
}

Texture * Material::GetTexture() const
{
	return this->_texture;
}

std::wstring Material::GetMaterialName()
{
	return name;
}

std::wstring Material::GetTextureName()
{
	return Kd_map;
}
