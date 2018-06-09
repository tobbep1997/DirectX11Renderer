#include "Texture.h"
#include "../../Window/Extern.h"


HRESULT Texture::_loadTexture(const wchar_t * path, ID3D11Resource *& r, ID3D11ShaderResourceView *& srv)
{
	return DirectX::CreateWICTextureFromFile(DX::g_device, DX::g_deviceContext, path, &r, &srv);
}

HRESULT Texture::_createSampler()
{
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	return DX::g_device->CreateSamplerState(&sampDesc, &this->_samplerState);
}

Texture::Texture()
{
	this->_resource = nullptr;
	this->_shaderResourceView = nullptr;
}


Texture::~Texture()
{
	DX::safeRelease(this->_resource);
	DX::safeRelease(this->_shaderResourceView);
	DX::safeRelease(this->_samplerState);
}

HRESULT Texture::LoadTexture(const std::string path)
{
	std::wstring ws(path.begin(), path.end());
	HRESULT texRes = _loadTexture(ws.c_str(), this->_resource, this->_shaderResourceView);
	HRESULT smpRes = _createSampler();

	if (FAILED(texRes))
		return texRes;
	if (FAILED(smpRes))
		return smpRes;

	return S_OK;
}

ID3D11Resource * Texture::GetResource() const
{
	return this->_resource;
}

ID3D11ShaderResourceView * Texture::GetShaderResourceView() const
{
	return this->_shaderResourceView;
}

ID3D11SamplerState * Texture::GetSamplerState() const
{
	return this->_samplerState;
}
