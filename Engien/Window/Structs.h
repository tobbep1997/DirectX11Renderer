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