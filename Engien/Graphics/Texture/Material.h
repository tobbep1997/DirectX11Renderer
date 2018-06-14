#pragma once
#include "Texture.h"
#include <string>
#include <DirectXMath.h>
#include <fstream>
#include <vector>
#include <iostream>

class Material
{
private:
	std::wstring name;
	std::wstring Kd_map;
	Texture * _texture;

private:
	void _loadMTL(const std::wstring & path, const std::wstring & matName);
	void _loadTexture(const std::wstring & path);
public:
	Material(const std::wstring & path = L"", const std::wstring & matName = L"");
	~Material();

	void LoadMTL(const std::wstring & path = L"", const std::wstring & matName = L"");
	void LoadTexture(const std::wstring & path = L"");

	Texture * GetTexture() const;

	std::wstring GetMaterialName();
	std::wstring GetTextureName();
};

