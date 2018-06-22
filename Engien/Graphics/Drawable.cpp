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
	for (unsigned int i = 0; i < this->_vertexBuffer.size(); i++)
		DX::safeRelease(this->_vertexBuffer[i]);

	this->_meshSize.push_back(size);
	
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(VERTEX) * size;
	
	ID3D11Buffer * b = nullptr;
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = V;
	HRESULT hr = DX::g_device->CreateBuffer(&bufferDesc, &vertexData, &b);
	this->_vertexBuffer.push_back(b);
}

void Drawable::_createMultBuffer(MESH mesh)
{
	for (unsigned int i = 0; i < this->_vertexBuffer.size(); i++)
		DX::safeRelease(this->_vertexBuffer[i]);


	//this->_vertexBuffer = new ID3D11Buffer*[mesh.vertex.size()];
	//this->_objectSize = static_cast<UINT>(mesh.vertex.size());
	//this->_meshSize = new UINT[mesh.vertex.size()];
	for (size_t i = 0; i < mesh.vertex.size(); i++)
	{


		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(VERTEX) * static_cast<UINT>(mesh.vertex[i].size());

		ID3D11Buffer * b;
		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = mesh.vertex[i].data();
		HRESULT hr = DX::g_device->CreateBuffer(&bufferDesc, &vertexData, &b);
		this->_vertexBuffer.push_back(b);
		this->_meshSize.push_back(static_cast<UINT>(mesh.vertex[i].size()));
	}
	this->_material = mesh.material;
}

Drawable::Drawable()
{
	this->_position	= XMFLOAT4A(0, 0, 0, 1);
	this->_scale	= XMFLOAT4A(1, 1, 1, 1);
	this->_rotation	= XMFLOAT4A(0, 0, 0, 1);
	this->_buildMatrix();
	//this->_material = nullptr;
	//this->_vertexBuffer = nullptr;
	//this->_meshSize = nullptr;
}

Drawable::~Drawable()
{
	for (unsigned int i = 0; i < this->_vertexBuffer.size(); i++)
		DX::safeRelease(this->_vertexBuffer[i]);
	
	for (unsigned int i = 0; i < this->_material.size(); i++)
		delete this->_material[i];

}

void Drawable::Draw()
{
	DX::geometry.push_back(this);
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
	for (unsigned int i = 0; i < this->_material.size(); i++)
		delete this->_material[i];
	this->_material.clear();
	this->_material.push_back(new Material());
	this->_material[0]->LoadTexture(std::wstring(path.begin(), path.end()));
}

std::vector<ID3D11Buffer *> Drawable::getVertexBuffer()
{
	return this->_vertexBuffer;
}

UINT * Drawable::getVertexSize()
{
	return this->_meshSize.data();
}

DirectX::XMFLOAT4X4A& Drawable::getWorldMatrix()
{
	return this->_worldMatrix;
}

std::vector<Material *> Drawable::GetMaterial()
{
	return this->_material;
}

size_t Drawable::getObjectSize()
{
	return this->_vertexBuffer.size();
}
