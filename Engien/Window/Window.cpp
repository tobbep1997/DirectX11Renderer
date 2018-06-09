#include "Window.h"
#include "Extern.h"

ID3D11Device*			DX::g_device;
ID3D11DeviceContext*	DX::g_deviceContext;

std::queue<Drawable*>	DX::geometry;
std::vector	<Light*>	DX::lights;

void DX::safeRelease(IUnknown * u)
{
	if (u)
		u->Release();
	u = NULL;
}


bool Window::_initWindow()
{
	HICON hIicon = (HICON)LoadImage( // returns a HANDLE so we have to cast to HICON
		NULL,				// hInstance must be NULL when loading from a file
		NULL,				// the icon file name
		IMAGE_ICON,			// specifies that the file is an icon
		0,					// width of the image (we'll specify default later on)
		0,					// height of the image
		LR_LOADFROMFILE |	// we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |	// default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED			// let the system release the handle when it's no longer used
	);

	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = StaticWndProc;
	wcex.hInstance = m_hInstance;
	wcex.lpszClassName = "Engien";
	wcex.hIcon = hIicon;
	if (!RegisterClassEx(&wcex))
	{
		m_hwnd = false;
		return false;
	}

	RECT rc = { 0, 0, static_cast<long>(m_width), static_cast<long>(m_height) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND handle = CreateWindow(
		wcex.lpszClassName,
		m_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		m_hInstance,
		this);

	m_hwnd = handle;
	return true;
}

HRESULT Window::_initDirect3DContext()
{
	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif //DEBUG

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = m_hwnd;								// the window to be used
	scd.SampleDesc.Count = m_sampleCount;                   // how many multisamples
	scd.Windowed = !m_fullscreen;							// windowed/full-screen mode

															// create a device, device context and swap chain using the information in the scd struct
	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,//D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_swapChain,
		&DX::g_device,
		NULL,
		&DX::g_deviceContext);

	if (SUCCEEDED(hr))
	{
		// get the address of the back buffer
		ID3D11Texture2D* pBackBuffer = nullptr;
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		// use the back buffer address to create the render target
		DX::g_device->CreateRenderTargetView(pBackBuffer, NULL, &m_backBufferRTV);
		//we are creating the standard depth buffer here.
		_createDepthBuffer();

		DX::g_deviceContext->OMSetRenderTargets(1, &m_backBufferRTV, m_depthStencilView);	//As a standard we set the rendertarget. But it will be changed in the prepareGeoPass
		pBackBuffer->Release();
	}
	return hr;
}

void Window::_createDepthBuffer()
{
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_width;
	depthStencilDesc.Height = m_height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = m_sampleCount;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Create the Depth/Stencil View
	HRESULT hr = DX::g_device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthBufferTex);
	hr = DX::g_device->CreateDepthStencilView(m_depthBufferTex, NULL, &m_depthStencilView);

}

void Window::_initViewPort()
{
	m_viewport.Width = static_cast<float>(m_width);
	m_viewport.Height = static_cast<float>(m_height);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
}

void Window::_setViewport()
{

	DX::g_deviceContext->RSSetViewports(1, &m_viewport);
}

void Window::_createBuffers()
{
	D3D11_BUFFER_DESC vertexConstant;
	vertexConstant.Usage = D3D11_USAGE_DYNAMIC;
	vertexConstant.ByteWidth = sizeof(VERTEX_BUFFER);
	vertexConstant.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vertexConstant.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexConstant.MiscFlags = 0;
	vertexConstant.StructureByteStride = 0;

	HRESULT hr = DX::g_device->CreateBuffer(&vertexConstant, nullptr, &m_constantBuffer);

	D3D11_BUFFER_DESC lightConstant;
	lightConstant.Usage = D3D11_USAGE_DYNAMIC;
	lightConstant.ByteWidth = sizeof(LIGHT_BUFFER);
	lightConstant.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightConstant.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightConstant.MiscFlags = 0;
	lightConstant.StructureByteStride = 0;

	hr = DX::g_device->CreateBuffer(&lightConstant, nullptr, &this->m_lightBuffer);
	D3D11_BUFFER_DESC cameraBuffer;
	cameraBuffer.Usage = D3D11_USAGE_DYNAMIC;
	cameraBuffer.ByteWidth = sizeof(CAMERA_BUFFER);
	cameraBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBuffer.MiscFlags = 0;
	cameraBuffer.StructureByteStride = 0;

	hr = DX::g_device->CreateBuffer(&cameraBuffer, nullptr, &this->m_cameraBuffer);

}

void Window::_createShaders()
{
	ID3DBlob * pVS = nullptr;

	HRESULT hr = D3DCompileFromFile(
		L"Shader/VertexShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"main",		// entry point
		"vs_5_0",		// shader model (target)
		0,				// shader compile options			// here DEBUGGING OPTIONS
		0,				// effect compile options
		&pVS,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	if (!FAILED(hr))
		DX::g_device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &m_vertexShader);

	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	hr = DX::g_device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &m_inputLayout);
	pVS->Release();
	DX::g_deviceContext->IASetInputLayout(m_inputLayout);


	ID3DBlob * pPS = nullptr;
	hr = D3DCompileFromFile(
		L"Shader/PixelShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"main",		// entry point
		"ps_5_0",		// shader model (target)
		0,				// shader compile options			// here DEBUGGING OPTIONS
		0,				// effect compile options
		&pPS,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	if (!FAILED(hr))
		DX::g_device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &m_pixelShader);
	pPS->Release();
	DX::g_deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	DX::g_deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
}

void Window::_present(int sync)
{
	m_swapChain->Present(0, 0);
}

void Window::_mapBuffers(Camera * camera)
{
	D3D11_MAPPED_SUBRESOURCE dataPtr;

	CAMERA_BUFFER camBuff;
	camBuff.position = camera->GetPosition();
	DX::g_deviceContext->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &dataPtr);
	memcpy(dataPtr.pData, &camBuff, sizeof(CAMERA_BUFFER));
	DX::g_deviceContext->Unmap(m_cameraBuffer, 0);

	DX::g_deviceContext->PSSetConstantBuffers(1, 1, &m_cameraBuffer);
}

void Window::_geometryPass(Camera * camera)
{
	UINT32 vertexSize = sizeof(VERTEX);
	UINT32 offset = 0;
	DX::g_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ID3D11Buffer * vertexBuffer;
	VERTEX_BUFFER V_Buffer;

	if (camera)
	{
		V_Buffer.viewProjection = camera->GetViewProjectionMatrix();
	}
	else {
		V_Buffer.viewProjection = DirectX::XMFLOAT4X4A();
	}


	D3D11_MAPPED_SUBRESOURCE dataPtr;
	while (!DX::geometry.empty())
	{
		vertexBuffer = DX::geometry.front()->getVertexBuffer();
		DX::g_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexSize, &offset);

		V_Buffer.worldMatrix = DX::geometry.front()->getWorldMatrix();

		DX::g_deviceContext->Map(m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &dataPtr);
		memcpy(dataPtr.pData, &V_Buffer, sizeof(VERTEX_BUFFER));
		DX::g_deviceContext->Unmap(m_constantBuffer, 0);
		
		DX::g_deviceContext->VSSetConstantBuffers(0, 1, &m_constantBuffer);
		ID3D11SamplerState * ss = DX::geometry.front()->GetTexture()->GetSamplerState();
		ID3D11ShaderResourceView * srv = DX::geometry.front()->GetTexture()->GetShaderResourceView();

		DX::g_deviceContext->PSSetSamplers(0, 1, &ss);
		DX::g_deviceContext->PSSetShaderResources(0, 1, &srv);

		DX::g_deviceContext->Draw(DX::geometry.front()->getVertexSize(), 0);

		DX::geometry.pop();
	}
	

}

void Window::_lightPass()
{
	LIGHT_BUFFER light_buffer;
	for (size_t i = 0; i < DX::lights.size(); i++)
	{
		light_buffer.info[i] = XMINT4(static_cast<int>(DX::lights.size()), DX::lights[i]->GetInfo(),0,0);
		light_buffer.position[i] = DX::lights[i]->GetPosition();
		light_buffer.direction[i] = DX::lights[i]->GetDirection();
		light_buffer.color[i] = DX::lights[i]->GetColor();
	}
	D3D11_MAPPED_SUBRESOURCE dataPtr;
	DX::g_deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &dataPtr);
	memcpy(dataPtr.pData, &light_buffer, sizeof(LIGHT_BUFFER));
	DX::g_deviceContext->Unmap(m_lightBuffer, 0);

	DX::g_deviceContext->PSSetConstantBuffers(0, 1, &m_lightBuffer);
}

void Window::_releaseIUnknown()
{
	DX::safeRelease(m_swapChain);
	DX::safeRelease(m_backBufferRTV);
	DX::safeRelease(m_depthStencilView);
	DX::safeRelease(m_depthBufferTex);
	DX::safeRelease(m_samplerState);
	DX::safeRelease(m_inputLayout);

	DX::safeRelease(m_vertexShader);
	DX::safeRelease(m_pixelShader);

	DX::safeRelease(m_constantBuffer);
	DX::safeRelease(m_lightBuffer);
	DX::safeRelease(m_cameraBuffer);


	DX::safeRelease(DX::g_deviceContext);
	DX::safeRelease(DX::g_device);
}

LRESULT Window::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pParent;
	if (uMsg == WM_CREATE)
	{
		pParent = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pParent);
	}
	else
	{
		pParent = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (!pParent) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	pParent->m_hwnd = hWnd;
	return pParent->WndProc(uMsg, wParam, lParam);
}

LRESULT Window::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		m_width = LOWORD(lParam);
		m_height = HIWORD(lParam);
		break;
		// ----- Keyboard Button -----
	case WM_KEYDOWN:

		// --------------------------------Subject for change!--------------------------------
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);

		break;
	
	}

	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

Window::Window(HINSTANCE h)
{
	m_hInstance = h;
	m_hwnd = nullptr;
	m_width = 0;
	m_height = 0;
	m_title = "";
	m_sampleCount = 1;
	m_fullscreen = FALSE;
	DX::g_device = nullptr;
	DX::g_deviceContext = nullptr;
	m_swapChain = nullptr;
	m_backBufferRTV = nullptr;
	m_depthStencilView = nullptr;
	m_depthBufferTex = nullptr;
	m_samplerState = nullptr;	

}

Window::~Window()
{
	this->_releaseIUnknown();
}

bool Window::Init(int width, int height, LPCSTR title, BOOL fullscreen)
{
	m_width = width;
	m_height = height;
	m_title = title;
	m_fullscreen = fullscreen;

	_initWindow();
	HRESULT hr = _initDirect3DContext();
	_initViewPort();
	_setViewport();

	ShowWindow(m_hwnd, 10);
	this->_createBuffers();
	this->_createShaders();
	return false;
}

void Window::PollEvents()
{
	if (PeekMessage(&m_msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}
}

bool Window::isOpen()
{
	return WM_QUIT != m_msg.message;
}

void Window::Clear()
{
	float c[4] = { 0.0f,0.0f,0.0f,1.0f };

	DX::g_deviceContext->ClearRenderTargetView(m_backBufferRTV, c);
	DX::g_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	DX::g_deviceContext->OMSetBlendState(nullptr, 0, 0xffffffff);

	DX::lights.clear();

}

void Window::Flush(Camera * camera)
{
	if (camera)
		this->_mapBuffers(camera);
	this->_lightPass();
	this->_geometryPass(camera);
	this->_present();
}
