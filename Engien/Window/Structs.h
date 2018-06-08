#pragma once
#include <DirectXMath.h>
struct VERTEX 
{
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
	DirectX::XMINT4		info[256];
	DirectX::XMFLOAT4A	position[256];
	DirectX::XMFLOAT4A	direction[256];
	DirectX::XMFLOAT4A	color[256];
};

struct CAMERA_BUFFER
{
	DirectX::XMFLOAT4A	position;
};