#pragma once
#include "../Graphics/Drawable.h"
#include "../Light/Light.h"
#include <DirectXMath.h>
#include <queue>

namespace DX {
	extern ID3D11Device*			g_device;
	extern ID3D11DeviceContext*		g_deviceContext;

	extern std::vector	<Drawable*>	geometry;
	extern std::vector	<Light*>	lights;

	extern DirectX::XMFLOAT4X4A		shadowViewProjection;

	extern void safeRelease(IUnknown * u);

}	
