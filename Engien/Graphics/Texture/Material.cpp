#include "Material.h"


void Material::_loadMTL(const std::wstring & path, const std::wstring & matName)
{
	std::wifstream in(path);
	if (!in.is_open())
	{
		std::cout << "Didn't find file" << std::endl;
		in.close();
		return;
	}

	std::wstring p = std::wstring(path);
	size_t t = p.find_last_of(L'/');
	p = p.substr(0, t + 1);

	bool firstObject = false;

	wchar_t input[256];
	wchar_t ipt[1024];

	bool skip = true;
	std::wstring inputConvert;
	while (!in.eof())
	{
		in.getline(input, 256);
		inputConvert = std::wstring(input);
		if (input[0] == L'#' && !skip) {}
		else if (inputConvert.substr(0, inputConvert.find(' ')) == L"newmtl")
		{
			swscanf_s(input, L"%*ls %ls", ipt, 1024);
			if (std::wstring(ipt) == matName)
				skip = false;
		}
		else if (inputConvert.substr(0, inputConvert.find(' ')) == L"map_Kd" && !skip) {
			swscanf_s(input, L"%*ls %ls", ipt, 1024);
			this->Kd_map = this->getPath(path) + this->getName(std::wstring(ipt));
			
			skip = true;
		}

		for (size_t i = 0; i < 256; i++)
		{
			input[i] = NULL;
		}
	}
	in.close();
	
	this->_loadTexture(this->Kd_map);
}

void Material::_loadTexture(const std::wstring & path)
{
	this->_texture = new Texture();
	this->_texture->LoadTexture(std::string(path.begin(), path.end()));
}

std::wstring Material::getName(const std::wstring & path)
{
	size_t t = path.find_last_of(L"/\\");
	return path.substr(t + 1);
}

std::wstring Material::getPath(const std::wstring & path)
{
	size_t t = path.find_last_of(L"/\\");
	return path.substr(0, t + 1);
}

Material::Material(const std::wstring & path, const std::wstring & matName)
{
	this->_texture = nullptr;
	this->_loadMTL(path, matName);
}

Material::~Material()
{
	delete this->_texture;
}

void Material::LoadMTL(const std::wstring & path, const std::wstring & matName)
{
	this->_loadMTL(path, matName);
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
