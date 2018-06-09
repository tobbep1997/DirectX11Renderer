#pragma once
#include "WICTextureLoader.h"
#include <d3d11.h>
#include <string>
class Texture
{
private:
	ID3D11Resource *			_resource;
	ID3D11ShaderResourceView *	_shaderResourceView;
	ID3D11SamplerState*			_samplerState;

protected:
	HRESULT _loadTexture(const wchar_t* path, ID3D11Resource *& r, ID3D11ShaderResourceView *& srv);
	HRESULT _createSampler();
public:
	Texture();
	~Texture();

	HRESULT LoadTexture(const std::string path);

	ID3D11Resource * GetResource() const;
	ID3D11ShaderResourceView * GetShaderResourceView() const;
	ID3D11SamplerState * GetSamplerState() const;
};

