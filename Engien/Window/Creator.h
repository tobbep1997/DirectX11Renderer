#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

namespace Creator
{
	template <typename T>
	void BufferCreator(ID3D11Buffer ** buffer, T data, const int size)
	{
		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(T) * size;

		D3D11_SUBRESOURCE_DATA d;
		d.pSysMem = &data;
		HRESULT hr = DX::g_device->CreateBuffer(&bufferDesc, &d, buffer);
	}
}