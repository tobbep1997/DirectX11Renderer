#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include "Structs.h"
#include "Creator.h"
#include "../Camera/Camera.h"
#include "Input.h"


using namespace DirectX;

class Window
{
private:
	IDXGISwapChain*				m_swapChain;
	ID3D11RenderTargetView*		m_backBufferRTV;
	ID3D11DepthStencilView*		m_depthStencilView;
	ID3D11Texture2D*			m_depthBufferTex;
	ID3D11SamplerState*			m_samplerState;

	D3D11_VIEWPORT				m_viewport;

	HINSTANCE					m_hInstance;
	HWND						m_hwnd;
	INT							m_width;
	INT							m_height;
	LPCSTR						m_title;
	MSG							m_msg = { 0 };

	INT							m_sampleCount;
	BOOL						m_fullscreen;
	
	ID3D11InputLayout*			m_inputLayout;

	ID3D11VertexShader*			m_vertexShader;
	ID3D11PixelShader*			m_pixelShader;

	ID3D11Buffer*				m_constantBuffer;
	ID3D11Buffer*				m_lightBuffer;
	ID3D11Buffer*				m_cameraBuffer;
	ID3D11Buffer*				m_texInfoBuffer;

	//Shadows
	ID3D11VertexShader*			m_vertexShadow;

	ID3D11InputLayout*			m_shadowInputLayout;

	ID3D11DepthStencilView*		m_shadowDepthStencilView;
	ID3D11Texture2D*			m_shadowDepthBufferTex;
	ID3D11SamplerState*			m_shadowSamplerState;
	ID3D11ShaderResourceView *	m_shadowShaderResourceView;

	ID3D11Buffer*				m_shadowBuffer;

	D3D11_VIEWPORT				m_shadowViewport;


private:
	bool _initWindow();
	HRESULT _initDirect3DContext();
	
	void _createDepthBuffer();
	void _initViewPort();
	void _setViewport();

	void _createBuffers();
	void _createShaders();

	void _present(int = 0);
	void _mapBuffers(Camera * camera);
	void _geometryPass(Camera * camera = nullptr);

	void _lightPass();

	void _loadShadow();
	void _shadowPass();

	void _releaseIUnknown();

	static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	Window(HINSTANCE);
	~Window();

	bool Init(int width, int height, LPCSTR title, BOOL fullscreen);
	void PollEvents();
	bool isOpen();
	void Clear();
	
	void Flush(Camera * camera = nullptr);
};

