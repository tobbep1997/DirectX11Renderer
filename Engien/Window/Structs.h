#pragma once
#include <DirectXMath.h>
#include "../Graphics/Texture/Material.h"
struct VERTEX 
{
	VERTEX()
	{
		this->pos = DirectX::XMFLOAT4();
		this->normal = DirectX::XMFLOAT3();
		this->uv = DirectX::XMFLOAT2();
	}
	VERTEX(DirectX::XMFLOAT4 pos, DirectX::XMFLOAT3 normal, DirectX::XMFLOAT2 uv)
	{
		this->pos = pos;
		this->normal = normal;
		this->uv = uv;
	}
	DirectX::XMFLOAT4 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;
};

struct VERTEX_BUFFER
{
	DirectX::XMFLOAT4X4A worldMatrix;
	DirectX::XMFLOAT4X4A viewProjection;
};

struct LIGHT_BUFFER
{
	DirectX::XMINT4		info[64];
	DirectX::XMFLOAT4A	position[64];
	DirectX::XMFLOAT4A	direction[64];
	DirectX::XMFLOAT4A	color[64];
};

struct CAMERA_BUFFER
{
	DirectX::XMFLOAT4A	position;
};

struct MESH
{
	std::vector<std::vector<VERTEX>>	vertex;
	std::vector<Material*>				material;
};