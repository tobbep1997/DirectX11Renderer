#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

#include "Extern.h"
class Creator
{
public:
	template <typename T>
	static void BufferCreator(ID3D11Buffer ** buffer, T data, const int size)
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

	static HRESULT createVertexShader(const std::wstring & path, ID3D11VertexShader ** vertexShader, ID3DBlob ** blob, bool releaseBlob = true, const std::string & entryPoint = "main") {

		DX::safeRelease(*blob);
		HRESULT hr = D3DCompileFromFile(
			path.c_str(),		// filename
			nullptr,			// optional macros
			nullptr,			// optional include files
			entryPoint.c_str(),	// entry point
			"vs_5_0",			// shader model (target)
			0,					// shader compile options			// here DEBUGGING OPTIONS
			0,					// effect compile options
			blob,				// double pointer to ID3DBlob		
			nullptr				// pointer for Error Blob messages.
								// how to use the Error blob, see here
								// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
		);
		if (!FAILED(hr)) {
			DX::g_device->CreateVertexShader((*blob)->GetBufferPointer(), (*blob)->GetBufferSize(), nullptr, vertexShader);
			if (releaseBlob)
				DX::safeRelease(*blob);
			return S_OK;
		}
		else
		{
			return hr;
		}
	}

	static HRESULT createPixelShader(const std::wstring & path, ID3D11PixelShader ** pixelShader, ID3DBlob ** blob, bool releaseBlob = true, const std::string & entryPoint = "main") {

		DX::safeRelease(*blob);
		HRESULT hr = D3DCompileFromFile(
			path.c_str(),		// filename
			nullptr,			// optional macros
			nullptr,			// optional include files
			entryPoint.c_str(),	// entry point
			"ps_5_0",			// shader model (target)
			0,					// shader compile options			// here DEBUGGING OPTIONS
			0,					// effect compile options
			blob,				// double pointer to ID3DBlob		
			nullptr				// pointer for Error Blob messages.
								// how to use the Error blob, see here
								// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
		);
		if (!FAILED(hr)) {
			DX::g_device->CreatePixelShader((*blob)->GetBufferPointer(), (*blob)->GetBufferSize(), nullptr, pixelShader);
			if (releaseBlob)
				DX::safeRelease(*blob);
			return S_OK;
		}
		else
		{
			return hr;
		}
	}
};