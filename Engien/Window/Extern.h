#pragma once
#include "../Graphics/Drawable.h"
#include "../Light/Light.h"
#include <queue>

namespace DX {
	extern ID3D11Device*			g_device;
	extern ID3D11DeviceContext*		g_deviceContext;

	extern std::queue	<Drawable*>	geometry;
	extern std::vector	<Light*>	lights;

	extern void safeRelease(IUnknown * u);

}	
