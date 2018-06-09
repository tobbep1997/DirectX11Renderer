#include "Drawable.h"
#include "../Window/Extern.h"



void Drawable::_buildMatrix()
{
	DirectX::XMMATRIX translation	= DirectX::XMMatrixTranslation(this->_position.x, this->_position.y, this->_position.z);
	DirectX::XMMATRIX scale			= DirectX::XMMatrixScaling(this->_scale.x, this->_scale.y, this->_scale.z);
	DirectX::XMMATRIX rotation		= DirectX::XMMatrixRotationRollPitchYaw(this->_rotation.x, this->_rotation.y, this->_rotation.z);
	
	DirectX::XMStoreFloat4x4A(&this->_worldMatrix, XMMatrixTranspose(rotation * scale * translation));
}

void Drawable::_createBuffer(VERTEX * V, const int& size)
{
	this->_meshSize = size;

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(VERTEX) * size;
	
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = V;
	HRESULT hr = DX::g_device->CreateBuffer(&bufferDesc, &vertexData, &this->_vertexBuffer);
}

Drawable::Drawable()
{
	this->_position	= XMFLOAT4A(0, 0, 0, 1);
	this->_scale	= XMFLOAT4A(1, 1, 1, 1);
	this->_rotation	= XMFLOAT4A(0, 0, 0, 1);
	this->_buildMatrix();
	this->_texture = new Texture();
}

Drawable::~Drawable()
{
	DX::safeRelease(this->_vertexBuffer);
	delete this->_texture;
}

void Drawable::Draw()
{
	DX::geometry.push(this);
}

void Drawable::SetPosition(DirectX::XMFLOAT4A p)
{
	this->_position = p;
	this->_buildMatrix();
}

void Drawable::SetRotation(float x, float y, float z, float w)
{
	this->SetRotation(DirectX::XMFLOAT4A(x, y, z, w));
}

void Drawable::SetPosition(float x, float y, float z, float w)
{
	this->SetPosition(DirectX::XMFLOAT4A(x, y, z, w));
}

void Drawable::SetRotation(DirectX::XMFLOAT4A r)
{
	this->_rotation = r;
	this->_buildMatrix();
}

void Drawable::SetScale(float x, float y, float z, float w)
{
	this->SetScale(DirectX::XMFLOAT4A(x, y, z, w));
}

void Drawable::SetScale(DirectX::XMFLOAT4A s)
{
	this->_scale = s;
	this->_buildMatrix();
}

DirectX::XMFLOAT4A Drawable::GetPosition() const
{
	return this->_position;
}

DirectX::XMFLOAT4A Drawable::GetRotation() const
{
	return this->_rotation;
}

DirectX::XMFLOAT4A Drawable::GetScale() const
{
	return this->_scale;
}

void Drawable::LoadTexture(const std::string & path)
{
	this->_texture->LoadTexture(path);
}

ID3D11Buffer * Drawable::getVertexBuffer()
{
	return this->_vertexBuffer;
}

UINT Drawable::getVertexSize()
{
	return this->_meshSize;
}

DirectX::XMFLOAT4X4A& Drawable::getWorldMatrix()
{
	return this->_worldMatrix;
}

Texture * Drawable::GetTexture()
{
	return this->_texture;
}
