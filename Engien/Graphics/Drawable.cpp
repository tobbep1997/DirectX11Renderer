#include "Drawable.h"
#include "../Window/Extern.h"



void Drawable::_buildMatrix()
{
	DirectX::XMMATRIX translation	= DirectX::XMMatrixTranslation(this->_position.x, this->_position.y, this->_position.z);
	DirectX::XMMATRIX scale			= DirectX::XMMatrixScaling(this->_scale.x, this->_scale.y, this->_scale.z);
	DirectX::XMMATRIX rotation		= DirectX::XMMatrixRotationRollPitchYaw(this->_roation.x, this->_roation.y, this->_roation.z);
	
	DirectX::XMStoreFloat4x4A(&this->_worldMatrix, XMMatrixTranspose(rotation * scale * translation));
}

Drawable::Drawable()
{
	this->_position	= XMFLOAT4A(0, 0, 0, 1);
	this->_scale	= XMFLOAT4A(1, 1, 1, 1);
	this->_roation	= XMFLOAT4A(0, 0, 0, 1);

	v[0].pos = DirectX::XMFLOAT4(0, 0.5, 0, 1);
	v[0].normal = DirectX::XMFLOAT3(0, 0, 1);
	v[0].uv = DirectX::XMFLOAT2(0, 0);

	v[1].pos = DirectX::XMFLOAT4(.5, -.5, 0, 1);
	v[1].normal = DirectX::XMFLOAT3(0, 0, 1);
	v[1].uv = DirectX::XMFLOAT2(1, 1);

	v[2].pos = DirectX::XMFLOAT4(-.5, -.5, 0, 1);
	v[2].normal = DirectX::XMFLOAT3(0, 0, 1);
	v[2].uv = DirectX::XMFLOAT2(0, 1);

	this->_meshSize = 3;

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(v);

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = v;
	HRESULT hr = DX::g_device->CreateBuffer(&bufferDesc, &vertexData, &this->_vertexBuffer);
}


Drawable::~Drawable()
{
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

void Drawable::SetRotation(DirectX::XMFLOAT4A r)
{
	this->_roation = r;
	this->_buildMatrix();
}

void Drawable::SetScale(DirectX::XMFLOAT4A s)
{
	this->_scale = s;
	this->_buildMatrix();
}

ID3D11Buffer * Drawable::getVertexBuffer()
{
	return this->_vertexBuffer;
}

UINT Drawable::getVertexSize()
{
	return this->_meshSize;
}
