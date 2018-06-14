#include "Material.h"




void Material::_loadMTL(const std::wstring & path, const std::wstring & matName)
{
	std::wifstream in(path);

	bool firstObject = false;

	if (!in.is_open())
	{
		std::cout << "Didn't find file" << std::endl;
		in.close();
		return;
	}
	wchar_t input[256];
	wchar_t ipt[1024];

	bool skip = true;
	std::wstring inputConvert;
	while (!in.eof())
	{
		in.getline(input, 256);
		inputConvert = std::wstring(input);
		if (input[0] == L'#' && !skip) {}
		else if (inputConvert.substr(0, inputConvert.find(' ')) == matName)
		{
			skip = false;
		}
		else if (inputConvert.substr(0, inputConvert.find(' ')) == L"map_Kd") {
			swscanf_s(input, L"%*ls %ls", ipt, 1024);
			this->Kd_map = std::wstring(ipt);
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
