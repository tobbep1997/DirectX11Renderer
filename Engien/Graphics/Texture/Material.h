#pragma once
#include "Texture.h"
#include <string>
#include <DirectXMath.h>

class Material
{
private:
	std::wstring name;
	std::wstring Kd_map;
	Texture * _texture;

private:
	void _loadMTL(const std::wstring & path);
	void _loadTexture(const std::wstring & path);
public:
	Material(const std::wstring & path = L"");
	~Material();

	void LoadMTL(const std::wstring & path = L"");
	void LoadTexture(const std::wstring & path = L"");

	Texture * GetTexture() const;


	std::wstring GetMaterialName();
	std::wstring GetTextureName();
};

