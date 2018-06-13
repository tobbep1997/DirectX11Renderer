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
	for (unsigned int i = 0; i < this->_objectSize; i++)
		DX::safeRelease(this->_vertexBuffer[i]);

	if (_meshSize)
		delete[] _meshSize;
	this->_meshSize = new UINT[1];

	this->_vertexBuffer = new ID3D11Buffer*[1];

	this->_objectSize = 1;
	this->_meshSize[0] = size;
	
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(VERTEX) * size;
	
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = V;
	HRESULT hr = DX::g_device->CreateBuffer(&bufferDesc, &vertexData, &this->_vertexBuffer[0]);
}

void Drawable::_createMultBuffer(std::vector<std::vector<VERTEX>> V)
{
	for (unsigned int i = 0; i < this->_objectSize; i++)
		DX::safeRelease(this->_vertexBuffer[i]);

	if (this->_meshSize)
		delete[] _meshSize;

	this->_vertexBuffer = new ID3D11Buffer*[V.size()];
	this->_objectSize = static_cast<UINT>(V.size());
	this->_meshSize = new UINT[V.size()];
	for (size_t i = 0; i < V.size(); i++)
	{

		this->_meshSize[i] = static_cast<UINT>(V[i].size());

		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(VERTEX) * static_cast<UINT>(V[i].size());

		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = V[i].data();
		HRESULT hr = DX::g_device->CreateBuffer(&bufferDesc, &vertexData, &this->_vertexBuffer[i]);
	}
}

Drawable::Drawable()
{
	this->_position	= XMFLOAT4A(0, 0, 0, 1);
	this->_scale	= XMFLOAT4A(1, 1, 1, 1);
	this->_rotation	= XMFLOAT4A(0, 0, 0, 1);
	this->_buildMatrix();
	this->_material = nullptr;
	this->_vertexBuffer = nullptr;
	this->_meshSize = nullptr;
}

Drawable::~Drawable()
{
	for (unsigned int i = 0; i < this->_objectSize; i++)
		DX::safeRelease(this->_vertexBuffer[i]);
	delete[] this->_vertexBuffer;
	for (unsigned int i = 0; i < this->_objectSize; i++)
		if (this->_material[i])
		{
			delete this->_material[0];
			this->_material[0] = nullptr;
		}
	delete[] this->_material;

	delete[] _meshSize;

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
	this->_material = new Material*[1];
	this->_material[0] = new Material(std::wstring(path.begin(), path.end()));
	this->_material[0]->LoadTexture(std::wstring(path.begin(), path.end()));
}

ID3D11Buffer ** Drawable::getVertexBuffer()
{
	return this->_vertexBuffer;
}

UINT * Drawable::getVertexSize()
{
	return this->_meshSize;
}

DirectX::XMFLOAT4X4A& Drawable::getWorldMatrix()
{
	return this->_worldMatrix;
}

Material ** Drawable::GetMaterial()
{
	return this->_material;
}

UINT Drawable::getObjectSize()
{
	return this->_objectSize;
}
